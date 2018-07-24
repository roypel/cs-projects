#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "MainAux.h"
#include "solver.h"
#include "gameStructs.h"
#include "linkedListFunc.h"

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

void checkCell(int x, int y, int z, board *check) {
	int i, j, erroneous = 0;
	for (i = 0; i < check->cols * check->rows; i++) {/*Check column*/
		if ((check->board[i][y].value == z) && (i != x)) {
			check->board[i][y].error = 1;
			erroneous = 1;
		}
	}
	for (i = 0; i < check->cols * check->rows; i++) {/*Check row*/
		if ((check->board[x][i].value == z) && (i != y)) {
			check->board[x][i].error = 1;
			erroneous = 1;
		}
	}
	for (i = (x / check->rows) * check->rows;
			i < (int) (x / check->rows) * check->rows + check->rows; i++) {
		for (j = (y / check->cols) * check->cols;
				j < (int) (y / check->cols) * check->cols + check->cols; j++) {/*Check block*/
			if (!((i == x) && (j == y))) {
				if (check->board[i][j].value == z) {
					check->board[i][j].error = 1;
					erroneous = 1;
				}
			}
		}
	}
	check->board[x][y].error = erroneous;
}

int isErroneous(gameState *metaBoard) {
	/*Checks if the whole board contains erroneous values for various functions*/
	int i, j;
	for (i = 0; i < metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->rows; j++) {
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
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check column*/
		if (i != x)
			checkCell(i, y, metaBoard->gameBoard->board[i][y].value,
					metaBoard->gameBoard);
	}
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check row*/
		if (i != y)
			checkCell(x, i, metaBoard->gameBoard->board[x][i].value,
					metaBoard->gameBoard);
	}
	for (i = (x / metaBoard->rows) * metaBoard->rows;
			i < (int) (x / metaBoard->rows) * metaBoard->rows + metaBoard->rows;
			i++) {
		for (j = (y / metaBoard->cols) * metaBoard->cols;
				j
						< (int) (y / metaBoard->cols) * metaBoard->cols
								+ metaBoard->cols; j++) {/*Check block*/
			if (!((i == x) && (j == y))) {

			}
		}
	}
}

void setBoard(int x, int y, int z, gameState *metaBoard) {
	int newMove[4];
	newMove[0] = x;
	newMove[1] = y;
	newMove[2] = metaBoard->gameBoard->board[x][y].value;
	newMove[3] = z;
	if (!metaBoard->gameBoard->board[x][y].fixed) {
		metaBoard->moves->currentMove = addNextMove(
				metaBoard->moves->currentMove, newMove, 1);
		if (z == 0) {/*User tries to erase a value on the board*/
			if (metaBoard->gameBoard->board[x][y].value > 0) {/*Check if we erase a value on the board or cell is already empty*/
				metaBoard->gameBoard->board[x][y].value = 0;
				metaBoard->gameBoard->board[x][y].error = 0;
				metaBoard->filledCells--;
				printBoard(metaBoard->gameBoard, metaBoard->markError);
			} else {
				printBoard(metaBoard->gameBoard, metaBoard->markError);
			}
		} else if (z == metaBoard->gameBoard->board[x][y].value) {/*Trying to re-enter value shouldn't change anything*/
			printBoard(metaBoard->gameBoard, metaBoard->markError);
		} else {
			if (metaBoard->gameBoard->board[x][y].value == 0) {
				metaBoard->filledCells++;
			}
			metaBoard->gameBoard->board[x][y].value = z;
			checkCell(x, y, z, metaBoard->gameBoard);
			printBoard(metaBoard->gameBoard, metaBoard->markError);
			checkErroneous(metaBoard, x, y);/*If we changed the value of a cell it might fixed an erroneous problem in different cells*/
			checkWin(metaBoard);
		}
	} else {
		printf("Error: cell is fixed\n");
	}
}

void hintBoard(int x, int y, gameState *metaBoard) {
	if (x < 1 || y < 1 || x > metaBoard->cols * metaBoard->rows
			|| y > metaBoard->cols * metaBoard->rows)
		printf("Error: value not in range 1-%d\n",
				metaBoard->cols * metaBoard->rows);
	else if (isErroneous(metaBoard))
		printf("Error: board contains erroneous values\n");
	else if (metaBoard->gameBoard->board[x][y].fixed)
		printf("Error: cell is fixed\n");
	else if (metaBoard->gameBoard->board[x][y].value)
		printf("Error: cell already contains a value\n");
	/*ADD ILP FUNCTION TO RETURN THE HINT PLEASE DONT DISSAPOINT ME FUTURE US*/
}

void validate(gameState *metaBoard) {
	int rows = metaBoard->gameBoard->rows;
	int cols = metaBoard->gameBoard->cols;
	board tempBoard;
	tempBoard.rows = rows;
	tempBoard.cols = cols;
	initalizeBoard(&tempBoard);
	copyBoard(metaBoard->gameBoard, &tempBoard);
	/*if (solver(&tempBoard, 0)) {
	 copyBoard(&tempBoard, metaBoard->solution);
	 printf("Validation passed: board is solvable\n");
	 } else {
	 printf("Validation failed: board is unsolvable\n");
	 }*/
	freeBoard(&tempBoard);
}

void numOfSol(board *tmpBoard) {
	int indexCounter[2] = { 0 };
	solver(tmpBoard, indexCounter);
	printf("Number of solutions:%d\n", indexCounter[1]);
	if (indexCounter[1] == 1)
		printf("This is a good board!\n");
	else if (indexCounter[1] != 0)
		printf("The puzzle has more than 1 solution, try to edit further\n");
}

void undo(gameState *metaBoard) {
	int i;
	int * moves = metaBoard->moves->currentMove->change;
	if (moves[0] != -1) {
		for (i = 1; i < (moves[0] * 3 + 1); i += 4) {
			setBoard(moves[i], moves[i + 1], moves[i + 2], metaBoard);
			printf("Undo %d,%d: from ", moves[i], moves[i + 1]);
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
		for (i = 1; i < (moves[0] * 3 + 1); i += 4) {
			setBoard(moves[i], moves[i + 1], moves[i + 3], metaBoard);
			printf("Redo %d,%d: from ", moves[i], moves[i + 1]);
			printChanges(moves[i + 2], moves[i + 3]);
		}
		metaBoard->moves->currentMove = metaBoard->moves->currentMove->next;
	} else
		printf("Error: no moves to redo\n");
}

void generateBoard(gameState *metaBoard) {
	int i, j;
	/*builder(metaBoard->solution, 0, 0);FUNCTION IS NOW OBSOLETE, DELETED! metaBoard->solution will contain a completely solved board*/
	hinter(metaBoard);/*Adding fixed cells to the board*/
	copyBoard(metaBoard->solution, metaBoard->gameBoard);
	for (i = 0; i < metaBoard->rows * metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->rows * metaBoard->cols; j++) {
			if (!metaBoard->gameBoard->board[i][j].fixed)
				metaBoard->gameBoard->board[i][j].value = 0;/*Erase unfixed cells in game board*/
		}
	}
}

void initalizeGame(gameState *metaBoard) {
	readBoard(metaBoard);/*Get number of hints and size of blocks from user (default 3*3 in this exercise)*/
	metaBoard->gameBoard->rows = metaBoard->rows;
	metaBoard->gameBoard->cols = metaBoard->cols;
	metaBoard->markError = 1;
	metaBoard->moves = (linkedList *) malloc(sizeof(linkedList));
	if (metaBoard->moves == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard->moves->currentMove = (node *) malloc(sizeof(node));
	if (metaBoard->moves->currentMove == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard->moves->currentMove->change = (int *) malloc(sizeof(int));
	if (metaBoard->moves->currentMove->change == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard->moves->currentMove->change[0] = -1;
	metaBoard->moves->firstNode = metaBoard->moves->currentMove;
	initalizeBoard(metaBoard->gameBoard);
	printBoard(metaBoard->gameBoard, metaBoard->markError);
}

void resetGame(gameState *metaBoard) {
	int* move;
	int i, j, counter;
	while (metaBoard->moves->currentMove != metaBoard->moves->firstNode) {
		move = metaBoard->moves->currentMove->change;
		counter = move[0];
		for (i = 0; i < counter; i++) {/*Enter values to board and check the cell for erroneous conflicts*/
			metaBoard->gameBoard->board[move[i * 4]][move[i * 4 + 1]].value =
					move[i * 4 + 2];
		}
	}
	counter = 0;
	for (i=0; i < metaBoard->cols; i++){
		for (j=0; j < metaBoard->rows; j++){
			if (metaBoard->gameBoard->board[i][j].value > 0)
				counter++;
			metaBoard->gameBoard->board[i][j].error = 0;
		}
	}
	metaBoard->filledCells = counter;
}

void exitGame(gameState *metaBoard) {
	printf("Exiting...\n");
	resetGame(metaBoard);
	free(metaBoard->solution);
	free(metaBoard->gameBoard);
	exit(0);
}