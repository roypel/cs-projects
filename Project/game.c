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

void eraseBoard(board *toErase) {
	int i, j;
	for (i = 0; i < toErase->cols * toErase->rows; i++) {
		for (j = 0; j < toErase->cols * toErase->rows; j++) {
			toErase->board[i][j].value = 0;
			toErase->board[i][j].error = 0;
			toErase->board[i][j].fixed = 0;
		}
	}
}

void initalizeBoard(board *newBoard) {
	int i;
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
	}
	eraseBoard(newBoard);
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

void setBoard(int x, int y, int z, gameState *metaBoard, int set) {/*The set boolean parameter is used in order to not advance the undo/redo list when not needed eg. undo/redo*/
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
		if (metaBoard->mode == Solve)
			checkWin(metaBoard);
	} else {
		printf("Error: cell is fixed\n");
	}
}
int* findFilled(gameState *metaBoard, int* amountFilled) {
	int *filled = {0};
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[j][i].value != 0) {
				filled = (int*) realloc(filled, ((*amountFilled) + 1) * 3 * sizeof(int));
				if (filled == NULL) {
					printf("Error: realloc has failed\n");
					exit(0);
				}
				filled[(*amountFilled) * 3] = j;
				filled[(*amountFilled) * 3 + 1] = i;
				filled[(*amountFilled) * 3 + 2] =
						metaBoard->gameBoard->board[j][i].value;
				(*amountFilled)++;
			}
		}
	}
	return filled;
}

int findval(double* sol, int x, int y, int cols, int rows) {
	int i;
	for (i = 0; i < cols * rows; i++) {
		if (sol[x * cols * rows + y * cols * rows * cols * rows + i])/*If the location has 1 then the value in the cell in the valid board is the location-1*/
			return i + 1;
	}
	return -1;/*Value not found, there was no valid solution, shouldn't happen since the function runs only if a valid solution was found*/
}

void eraseRandom(int erase, gameState *metaBoard) {
	/*The function randomly chooses cells (first column then row) which will be fixed for the current game, by the value the user entered on the beginning of the game.
	 *The function updates the solution board of the gameState metaBoard with the correct cells to be fixed, while the rest of the cells remains unfixed, and no value is being changed on the board.
	 *INPUT: gameState *metaBoard - a pointer to a gameState with a completely filled solution board and a field filledCells with the user input of the amount of cells they wish to be filled.*/
	int num, cols = metaBoard->cols, rows = metaBoard->rows, x, y;
	while (erase) {/*As long as we need to add more hints*/
		num = rand() % (cols * rows * cols * rows);/*Get an index for next cell to erase*/
		x = num % (cols * rows);
		y = (int) (num / (rows * cols));
		if (metaBoard->gameBoard->board[x][y].value != 0) {
			metaBoard->gameBoard->board[x][y].value = 0;
			erase--;
		}
	}
}

int tryFill(int fill, int* values, int* filledCells, gameState *metaBoard) {
	int amountFilled = 0, num, x = 0, y = 0, flag = 1, i;
	int cols = metaBoard->cols, rows = metaBoard->rows;/*CONTINUE HERE, make fill board good and send from generate to here, run 1000 iterations and try again if no solution or a cell has no values*/
	while (amountFilled < fill) {
		for (i = 0; i < cols * rows; i++) {
			values[i] = 0;
		}
		while (flag) {
			num = rand() % (cols * rows * cols * rows);/*Get an index for next cell to enter*/
			x = num % (cols * rows);
			y = (int) (num / (rows * cols));
			if (metaBoard->gameBoard->board[x][y].value == 0)
				flag = 0;/*Found an empty cell to fill*/
		}
		flag = 1;
		while (flag) {
			for (i = 0; i < cols * rows; i++) {/*Check if there are values we didn't use yet*/
				if (!values[i])
					flag = 0;
			}
			if (flag)
				return 0;/*Can't find value for this cell, clear the board and start again*/
			num = rand() % (cols * rows);/*Get a value to try to enter the x,y cell*/
			if (values[num] == 0) {/*We haven't tried this value yet*/
				values[num]++;
				checkCell(x, y, num, 0, metaBoard->gameBoard);
				if (!metaBoard->gameBoard->board[x][y].error) {
					flag = 0;/*Found a legal value to enter*/
					metaBoard->gameBoard->board[x][y].value = num;
					filledCells[amountFilled * 3] = x;/*Update filled cells array to keep track of changes*/
					filledCells[amountFilled * 3 + 1] = y;
					filledCells[amountFilled * 3 + 2] = num;
					amountFilled++;
				} else
					metaBoard->gameBoard->board[x][y].error = 0;
			}
		}
	}
	return 1;
}

void hintBoard(int x, int y, gameState *metaBoard) {
	int rows = metaBoard->rows, cols = metaBoard->cols;
	double *sol;
	int* filledCells;
	int amountFilled = 0;
	int val, solved;
	if (metaBoard->gameBoard->board[x][y].fixed)
		printf("Error: cell is fixed\n");
	else if (metaBoard->gameBoard->board[x][y].value)
		printf("Error: cell already contains a value\n");
	/*TODO: ADD ILP FUNCTION TO RETURN THE HINT PLEASE DONT DISSAPOINT ME FUTURE US, check if free works properly when realloc was in different place*/
	else {
		sol = (double*) calloc(cols * rows * cols * rows * cols * rows,
				sizeof(double));
		if (sol == NULL) {
			printf("Error: calloc has failed\n");
			exit(0);
		}
		filledCells = findFilled(metaBoard, &amountFilled);/*Get the already filled cells from the board*/
		solved = findSol(cols, rows, filledCells, amountFilled, sol);
		if (solved > 0) {/*Solution was found, we can give a hint*/
			val = findval(sol, x, y, cols, rows);
			printf("Hint: set cell to %d\n", val);
		} else if (!solved) {
			printf("Error: board is unsolvable\n");/*solved is 0 here so board is unsolveable*/
		}/*If we didn't enter the conditions above, we had an error in the Gurobi library and a message was printed*/
		free(filledCells);
		free(sol);
	}
}

int validate(gameState *metaBoard) {/*We need this for save as well, so we return a value and not print right away*/
	int rows = metaBoard->gameBoard->rows;
	int cols = metaBoard->gameBoard->cols;
	int solved, amountFilled = 0;
	int* filled;
	double *sol = (double*) calloc(cols * rows * cols * rows * cols * rows,
			sizeof(int));
	if (sol == NULL) {
		printf("Error: calloc has failed\n");
		exit(0);
	}
	filled = findFilled(metaBoard, &amountFilled);
	solved = findSol(cols, rows, filled, amountFilled, sol);
	free(filled);
	free(sol);
	return solved;/*Solved will return -1 on Gurobi failure, 0 on unsolvable board and 1 if a solution was found*/

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

void generateBoard(int fill, int keep, gameState *metaBoard) {
	int i, *filledCells, *values;
	int cols = metaBoard->cols, rows = metaBoard->rows;
	double *sol;
	sol = (double*) calloc(cols * rows * cols * rows * cols * rows,
			sizeof(double));
	if (sol == NULL) {
		printf("Error: calloc has failed\n");
		exit(0);
	}
	filledCells = (int *) malloc(sizeof(int) * fill * 3);
	if (filledCells == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	values = (int *) malloc(sizeof(int) * cols * rows);
	if (values == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	for (i = 0; i < 1000; i++) {
		if (!tryFill(fill, values, filledCells, metaBoard))
			eraseBoard(metaBoard->gameBoard);
		else if (findSol(cols, rows, filledCells, fill, sol) > 0) {
			eraseRandom(cols * rows * cols * rows - keep, metaBoard);
			printBoard(metaBoard);
			return;
		} else
			eraseBoard(metaBoard->gameBoard);
	}
	eraseBoard(metaBoard->gameBoard);
	printf("Error: puzzle generator failed\n");
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
