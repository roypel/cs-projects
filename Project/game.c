#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "MainAux.h"
#include "solver.h"
#include "gameStructs.h"
#include "linkedListFunc.h"
#include "gurobi_func.h"

void freeBoard(board *freeBird) {
	/*The function frees the memory allocated for the board in the input, starting from each row and then frees the board itself.
	 *INPUT: board *freeBird - a pointer to an allocated board which can be free to reduce the needed resources of the program.*/
	int i;
	for (i = 0; i < freeBird->rows * freeBird->cols; i++) {
		free((freeBird->board)[i]);
	}
	free(freeBird->board);
}

void initalizeBoard(board *newBoard) {
	int i, j;
	newBoard->board = (cell**) calloc(newBoard->rows * newBoard->cols,
			sizeof(cell *));
	if (newBoard->board == NULL) {
		printf("Error: calloc has failed\n");
		exit(0);
	}
	for (i = 0; i < newBoard->rows * newBoard->cols; i++) {
		newBoard->board[i] = (cell*) calloc(newBoard->rows * newBoard->cols,
				sizeof(cell));
		if (newBoard->board[i] == NULL) {
			printf("Error: calloc has failed\n");
			exit(0);
		}
		for (j = 0; j < newBoard->rows * newBoard->cols; j++) {
			newBoard->board[i][j].value = 0;
			newBoard->board[i][j].fixed = 0;
			newBoard->board[i][j].error = 0;
		}
	}
}

void copyBoard(board *srcBoard, board *trgtBoard) {
	/*The function copies the values of the given board srcBoard to the board trgtBoard.
	 *INPUT: board *srcBoard - a pointer to a valid board filled with values ranging from 0 to the board length, while 0 represents an empty cell, that all it's values will be copied to trgtBoard.
	 *		 board *trgtBoard - a pointer to a preallocated board with the same sizes as srcBoard, which will have the same values in each cell as srcBoard at the end of the function.*/
	int i, j;
	for (i = 0; i < srcBoard->cols * srcBoard->rows; i++) {
		for (j = 0; j < srcBoard->rows * srcBoard->cols; j++) {
			trgtBoard->board[i][j].value = srcBoard->board[i][j].value;
		}
	}
}

void checkCell(int x, int y, int z, int change, board *check) {
	int i, j, erroneous = 0;
	if (z != 0) {
		for (i = 0; i < check->cols * check->rows; i++) {/*Check row*/
			if ((check->board[i][y].value == z) && (i != x)) {
				if (!check->board[i][y].fixed)
					check->board[i][y].error = 1 * change;
				erroneous = 1;
			}
		}
		for (i = 0; i < check->cols * check->rows; i++) {/*Check column*/
			if ((check->board[x][i].value == z) && (i != y)) {
				if (!check->board[x][i].fixed)
					check->board[x][i].error = 1 * change;
				erroneous = 1;
			}
		}
		for (i = (x / check->cols) * check->cols;
				i < (int) (x / check->cols) * check->cols + check->cols; i++) {
			for (j = (y / check->rows) * check->rows;
					j < (int) (y / check->rows) * check->rows + check->rows;
					j++) {/*Check block*/
				if (!((i == x) && (j == y))) {
					if (check->board[i][j].value == z) {
						if (!check->board[i][j].fixed)
							check->board[i][j].error = 1 * change;
						erroneous = 1;
					}
				}
			}
		}
	}
	check->board[x][y].error = erroneous;
}

int isErroneous(gameState *metaBoard) {
	/*Checks if the whole board contains erroneous values for various functions*/
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[i][j].error == 1)
				return 1;
		}
	}
	return 0;

	/*int i, j;
	 for (i = 0; i < metaBoard->cols; i++) {
	 for (j = 0; j < metaBoard->rows; j++) {
	 checkCell(i, j, metaBoard->gameBoard->board[i][j].value,
	 metaBoard->gameBoard);
	 if (metaBoard->gameBoard->board[i][j].error == 1)
	 return 1;
	 }
	 }
	 return 0;*/
}

void checkWin(gameState *metaBoard) {
	int cols = metaBoard->gameBoard->cols;
	int rows = metaBoard->gameBoard->rows;
	if (metaBoard->filledCells == cols * cols * rows * rows) {
		if (!isErroneous(metaBoard)) {
			printf("Puzzle solved successfully\n");
			metaBoard->mode = Init;
		} else
			printf("Puzzle solution erroneous\n");
	}
}

void checkErroneous(gameState *metaBoard, int x, int y) {
	/*The function checks the column, row and block of cell x,y to check if any erroneous values are now fixed*/
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check row*/
		if (i != x)
			checkCell(i, y, metaBoard->gameBoard->board[i][y].value, 1,
					metaBoard->gameBoard);
	}
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check column*/
		if (i != y)
			checkCell(x, i, metaBoard->gameBoard->board[x][i].value, 1,
					metaBoard->gameBoard);
	}
	for (i = (x / metaBoard->cols) * metaBoard->cols;
			i < (int) (x / metaBoard->cols) * metaBoard->cols + metaBoard->cols;
			i++) {
		for (j = (y / metaBoard->rows) * metaBoard->rows;
				j
						< (int) (y / metaBoard->rows) * metaBoard->rows
								+ metaBoard->rows; j++) {/*Check block*/
			if (!((i == x) && (j == y))) {
				checkCell(i, j, metaBoard->gameBoard->board[i][j].value, 1,
						metaBoard->gameBoard);
			}
		}
	}
}

void setBoard(int x, int y, int z, gameState *metaBoard, int set) {/*the set boolean parameter is used in order to not advance the undo/redo list when not needed eg. undo/redo*/
	int newMove[4];
	newMove[0] = x;
	newMove[1] = y;
	newMove[2] = metaBoard->gameBoard->board[x][y].value;
	newMove[3] = z;
	if (!metaBoard->gameBoard->board[x][y].fixed) {
		if (set)
			metaBoard->moves->currentMove = addNextMove(
					metaBoard->moves->currentMove, newMove, 1);
		if (z == 0) {/*User tries to erase a value on the board*/
			if (metaBoard->gameBoard->board[x][y].value > 0) {/*Check if we erase a value on the board or cell is already empty*/
				metaBoard->gameBoard->board[x][y].value = 0;
				metaBoard->gameBoard->board[x][y].error = 0;
				metaBoard->filledCells--;
				checkErroneous(metaBoard, x, y);/*If we changed the value of a cell it might fixed an erroneous problem in different cells*/
			}
		} else if (z != metaBoard->gameBoard->board[x][y].value) {/*We don't re-enter the same value, so changes should be made*/
			if (metaBoard->gameBoard->board[x][y].value == 0) {
				metaBoard->filledCells++;
			}
			metaBoard->gameBoard->board[x][y].value = z;
			checkCell(x, y, z, 1, metaBoard->gameBoard);
			checkErroneous(metaBoard, x, y);/*If we changed the value of a cell it might fixed an erroneous problem in different cells*/
		}
		if (set)
			printBoard(metaBoard);
		checkWin(metaBoard);
	} else {
		printf("Error: cell is fixed\n");
	}
}

void hintBoard(int x, int y, gameState *metaBoard) {
	int rows = metaBoard->rows, cols = metaBoard->cols;
	double *sol;
	if (x < 1 || y < 1 || x > cols * rows || y > cols * rows)
		printf("Error: value not in range 1-%d\n",
				metaBoard->cols * metaBoard->rows);
	else if (isErroneous(metaBoard))
		printf("Error: board contains erroneous values\n");
	else if (metaBoard->gameBoard->board[x][y].fixed)
		printf("Error: cell is fixed\n");
	else if (metaBoard->gameBoard->board[x][y].value)
		printf("Error: cell already contains a value\n");
	/*ADD ILP FUNCTION TO RETURN THE HINT PLEASE DONT DISSAPOINT ME FUTURE US*/
	else {
		sol = (double*) calloc(cols * rows * cols * rows * cols * rows,
				sizeof(int));
		if (sol[0] == 0) {/*TODO This is also a lie, supposedto be if board solved or not*/
			printf("Hint: set cell to %f", sol[x]);/*TODO: erase this lie*/
		} else
			printf("Error: board is unsolvable\n");
	}
}

int validate(gameState *metaBoard) {
	int rows = metaBoard->gameBoard->rows;
	int cols = metaBoard->gameBoard->cols;
	double *sol = (double*) calloc(cols * rows * cols * rows * cols * rows,
			sizeof(int));
	if (sol[0] == 0)/*TODO: erase this lie, supposed to be solution was found*/
		return 1;
	return 0;

}

void numOfSol(board *gameBoard) {
	int solutions = solver(gameBoard);
	printf("Number of solutions:%d\n", solutions);
	if (solutions == 1)
		printf("This is a good board!\n");
	else if (solutions != 0)
		printf("The puzzle has more than 1 solution, try to edit further\n");
}

void undo(gameState *metaBoard) {
	int i;
	int * moves = metaBoard->moves->currentMove->change;
	if (moves[0] != -1) {
		for (i = 1; i < (moves[0] * 4 + 1); i += 4) {
			setBoard(moves[i], moves[i + 1], moves[i + 2], metaBoard, 0);
		}
		printBoard(metaBoard);
		for (i = 1; i < (moves[0] * 4 + 1); i += 4) {
			printf("Undo %d,%d: from ", moves[i] + 1, moves[i + 1] + 1);
			printChanges(moves[i + 3], moves[i + 2]);
		}
		metaBoard->moves->currentMove = metaBoard->moves->currentMove->prev;
	} else
		printf("Error: no moves to undo\n");
}

void redo(gameState *metaBoard) {
	int i;
	int * moves;
	if (metaBoard->moves->currentMove->next != NULL) {
		moves = metaBoard->moves->currentMove->next->change;
		for (i = 1; i < (moves[0] * 4 + 1); i += 4) {
			setBoard(moves[i], moves[i + 1], moves[i + 3], metaBoard, 0);
		}
		printBoard(metaBoard);
		for (i = 1; i < (moves[0] * 4 + 1); i += 4) {
			printf("Redo %d,%d: from ", moves[i] + 1, moves[i + 1] + 1);
			printChanges(moves[i + 2], moves[i + 3]);
		}
		metaBoard->moves->currentMove = metaBoard->moves->currentMove->next;
	} else
		printf("Error: no moves to redo\n");
}

void generateBoard(gameState *metaBoard) {
	int i, j;
	int cols = metaBoard->cols, rows = metaBoard->rows;
	double *sol = (double*) calloc(cols * rows * cols * rows * cols * rows,
			sizeof(int));
	/*builder(metaBoard->solution, 0, 0);FUNCTION IS NOW OBSOLETE, DELETED! metaBoard->solution will contain a completely solved board*/
	hinter(metaBoard);/*Adding fixed cells to the board*/
	copyBoard(metaBoard->solution, metaBoard->gameBoard);
	for (i = 0; i < metaBoard->rows * metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->rows * metaBoard->cols; j++) {
			if (!metaBoard->gameBoard->board[i][j].fixed)
				metaBoard->gameBoard->board[i][j].value = 0;/*Erase unfixed cells in game board*/
		}
	}
	if (sol[0] == 0)/*TODO: erase this lie*/
		printf("The Cake");
}

void resetGame(gameState *metaBoard) {
	int* move;
	int i, j, counter;
	while (metaBoard->moves->currentMove->change[0] != -1) {
		move = metaBoard->moves->currentMove->change;
		counter = move[0];
		for (i = 0; i < counter; i++) {/*Enter values to board and check the cell for erroneous conflicts*/
			metaBoard->gameBoard->board[move[i * 4 + 1]][move[i * 4 + 2]].value =
					move[i * 4 + 3];
		}
		metaBoard->moves->currentMove = metaBoard->moves->currentMove->prev;
	}
	counter = 0;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[j][i].value > 0)
				counter++;
			checkCell(j, i, metaBoard->gameBoard->board[j][i].value, 1,
					metaBoard->gameBoard);
		}
	}
	metaBoard->filledCells = counter;
	removeAllNext(metaBoard->moves->firstNode->next); /*Clear undo/redo list*/
	metaBoard->moves->currentMove = metaBoard->moves->firstNode;
	metaBoard->moves->currentMove->next = NULL;
	printf("Board reset\n");
}

void exitGame(gameState *metaBoard) {
	printf("Exiting...\n");
	removeAllNext(metaBoard->moves->firstNode);
	free(metaBoard->moves);
	freeBoard(metaBoard->gameBoard);
	free(metaBoard->gameBoard);
	exit(0);
}
