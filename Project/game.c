/*Source file which contains the functions that we use in order to execute the different commands of the game*/

#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "fileFunc.h"
#include "gameStructs.h"
#include "gurobiFunc.h"
#include "linkedListFunc.h"
#include "mainAux.h"

void checkErroneous(gameState *metaBoard, int x, int y) {
	/*The function checks the column, row and block of cell x,y to check if any erroneous values are now fixed.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with allocated board and valid values in it, where each erroneous cell is marked by the error property of the cell.
	 *        int x,y - Integers representing the column and row of the cell that was changed by <x,y>.*/
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check row*/
		if (i != x)
			checkCell(i, y, metaBoard->gameBoard->board[i][y].value, 1, metaBoard->gameBoard);
	}
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check column*/
		if (i != y)
			checkCell(x, i, metaBoard->gameBoard->board[x][i].value, 1, metaBoard->gameBoard);
	}
	for (i = (x / metaBoard->cols) * metaBoard->cols; i < (int) (x / metaBoard->cols) * metaBoard->cols + metaBoard->cols; i++) {
		for (j = (y / metaBoard->rows) * metaBoard->rows; j < (int) (y / metaBoard->rows) * metaBoard->rows + metaBoard->rows; j++) {/*Check block*/
			if (!((i == x) && (j == y))) {
				checkCell(i, j, metaBoard->gameBoard->board[i][j].value, 1, metaBoard->gameBoard);
			}
		}
	}
}

int* findFilled(gameState *metaBoard, int *amountFilled) {
	/*The function finds all the filled cells in the game board and return them in an array such that every cells take 3 spaces, x,y, and the value in this cell.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with allocated board and with valid values.
	 *        int *amountFilled - A pointer to an integer that will be updated with the amount of filled cells the function have found.
	 * OUTPUT: An int array with all the filled cells found in the game board, each cell uses 3 spaces in the format x,y, and the current value inside the cell.*/
	int *filled = { 0 };
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[j][i].value != 0) {
				filled = (int*) realloc(filled, ((*amountFilled) + 1) * 3 * sizeof(int));
				checkInitalize(filled, "realloc");
				filled[(*amountFilled) * 3] = j;
				filled[(*amountFilled) * 3 + 1] = i;
				filled[(*amountFilled) * 3 + 2] = metaBoard->gameBoard->board[j][i].value;
				(*amountFilled)++;
			}
		}
	}
	return filled;
}

int findval(double *sol, int x, int y, int cols, int rows) {
	/*The function extract the value that should be in the cell <x,y> according to the solution found with the ILP module that is contained in sol.
	 * INPUT: double *sol - A double array in the size of (cols * rows)^3, where the solution found by the ILP is stored. Function should run only if the solution is valid.
	 *        int x,y - Integers representing the column and row of the cell we want to know it's value according to the solution sol.
	 *        int cols, rows - Integers representing the amount of columns and rows in each block of the game board.
	 * OUTPUT: An integer which should be in the cell <x,y> according to the solution sol.*/
	int i;
	for (i = 0; i < cols * rows; i++) {
		if (sol[x * cols * rows + y * cols * rows * cols * rows + i])/*If the location has 1 then the value in the cell in the valid board is the location-1*/
			return i + 1;
	}
	return -1;/*Value not found, there was no valid solution, shouldn't happen since the function runs only if a valid solution was found*/
}

void keepRandom(int toKeep, gameState *metaBoard, double *sol) {
	/*The function randomly chooses cells to fill according to the board solution, sol. Fills a total of toKeep values.
	 *INPUT: int toKeep - An integer representing how many cells we need to randomly choose to keep with values.
	 *       gameState *metaBoard - A pointer to a gameState with allocated board and with valid values (if any at all), by the end of the function, the board will have toKeep values in it according to the solution sol.
	 *       double *sol - A double array in the size of (cols * rows)^3, where the solution found by the ILP is stored. Function should run only if the solution is valid.*/
	int num, cols = metaBoard->cols, rows = metaBoard->rows, x, y;
	eraseBoard(metaBoard->gameBoard);
	while (toKeep) {/*As long as we need to keep more values*/
		num = rand() % (cols * rows * cols * rows);/*Get an index for next cell to erase*/
		x = num % (cols * rows);
		y = (int) (num / (rows * cols));
		if (metaBoard->gameBoard->board[x][y].value == 0) {
			metaBoard->gameBoard->board[x][y].value = findval(sol, x, y, cols, rows);
			toKeep--;
		}
	}
}

int randEmptyCell(int *x, int *y, gameState *metaBoard) {
	/*The function tries to randomly find an index in the game board without any value.
	 * INPUT: int *x,*y - Pointers to integers representing the <x,y> cell, will be updated according to the index the function randomly chose.
	 *        gameState *metaBoard - A pointer to a gameState with allocated board with valid values.
	 * OUTPUT: The function returns (1) if the randomly chosen cell is empty, and (0) if it's not empty.*/
	int num, cols = metaBoard->cols, rows = metaBoard->rows;
	num = rand() % (cols * rows * cols * rows);/*Get an index for next cell to enter*/
	*x = num % (cols * rows);
	*y = (int) (num / (rows * cols));
	if (metaBoard->gameBoard->board[*x][*y].value == 0)
		return 1;/*Found an empty cell to fill*/
	return 0;
}

int checkRemainingValues(int cols, int rows, int *values) {
	/*The function checks if there are any values we still didn't try to enter to a cell, where the information of previous attempts stored in values.
	 * INPUT: - int cols, rows - Integers representing the amount of columns and rows in each block of the game board.
	 *          int *values - An integer array where the i cell is 0 if we hadn't tried the i value yet, or 1 if we already tried it.
	 * OUTPUT: The function return (1) if it found a value we still havn't tried to enter to the cell, or (0) if no value was found.*/
	int i;
	for (i = 0; i < cols * rows; i++) {/*Check if there are values we didn't use yet*/
		if (!values[i])
			return 1;
	}
	return 0;
}

int tryRandValue(int x, int y, int amountFilled, int *values, int *filledCells, gameState *metaBoard) {
	/*The function randomly chooses a value to enter to the <x,y> cell. If it's a legal value, updates parameters accordingly, or revert the changes if it's not legal.
	 * INPUT: int x,y - Integers representing the cell <x,y> we try to fill with a random value. The cell should be empty.
	 *        int amountFilled - Integer representing the amount of cells we already filled in the board, used to calculate the next cell to update in the filledVells array.
	 *        int *values - Integer array representing the values we already tried to fill in the <x,y> cell, 0 in the i cell indicates we haven't tried the i value yet, 1 indicates we already tried.
	 *        int *filledCells - An array holding the information of all the cells we filled, each cell takes 3 spaces, holding x, y and the value we entered.
	 *        gameState *metaBoard - A pointer to a gameState with allocated board with valid values we are trying to randomly fill.
	 * OUTPUT: The function return (1) if it found a legal value to enter to the <x,y> cell, and (0) if the randomly chosen value wasn't legal.*/
	int num = rand() % (metaBoard->cols * metaBoard->rows);/*Get a value to try to enter the x,y cell*/
	if (values[num] == 0) {/*We haven't tried this value yet*/
		values[num++]++;
		checkCell(x, y, num, 0, metaBoard->gameBoard);
		if (!metaBoard->gameBoard->board[x][y].error) {/*Found a legal value to enter*/
			metaBoard->gameBoard->board[x][y].value = num;
			filledCells[amountFilled * 3] = x;/*Update filled cells array to keep track of changes*/
			filledCells[amountFilled * 3 + 1] = y;
			filledCells[amountFilled * 3 + 2] = num;
			return 1;
		}
	}
	metaBoard->gameBoard->board[x][y].error = 0;
	metaBoard->gameBoard->board[x][y].value = 0;
	return 0;
}

int tryFill(int toFill, int *values, int *filledCells, gameState *metaBoard) {
	/*The function tries to randomly fill into the game board toFill legal cells, while updating the already filled cells in the filledCells array
	 * INPUT: int toFill - The amount of cells the function tries to randomly fill into the board, should not surpass the number of total cells in the game board ((cols*rows)^2)
	 *        int *values - An array that track the values we tried to fill into each cell, 0 in the i cell means we didn't tried the value yet, 1 indicates we already tried it.
	 *                      If the array is filled with 1, we couldn't find a legal value to the cell, and we failed in the filling. Allocated outside so we can recycle the same space.
	 *        int *filledCells - An array that keeps track of what cells we filled and with what values, each cell takes 3 spaces in the array, x, y, and the value we entered.
	 *        gameState *metaBoard - A pointer to a gameState with allocated board with valid values we are trying to randomly fill.
	 * OUTPUT: The function returns (1) if it could randomly fill toFill cells into the game board, and (0) if we couldn't find a legal value to one of the cells.*/
	int amountFilled = 0, x = 0, y = 0, i;
	int cols = metaBoard->cols, rows = metaBoard->rows;
	while (amountFilled < toFill) {
		for (i = 0; i < cols * rows; i++) {
			values[i] = 0;
		}
		while (!randEmptyCell(&x, &y, metaBoard))
			;/*Find empty cell in the board using random generator*/
		while (checkRemainingValues(cols, rows, values)) {
			if (tryRandValue(x, y, amountFilled, values, filledCells, metaBoard)) {
				amountFilled++;
				break;
			}
		}
		if (!checkRemainingValues(cols, rows, values) && (!metaBoard->gameBoard->board[x][y].value))
			return 0;/*Can't find value for this cell, clear the board and start again*/
	}
	return 1;
}

void checkWin(gameState *metaBoard) {
	/*The function checks if the board is completely filled correctly, and prints an according message and change the gameMode to Init if needed.
	 *INPUT: gameState *metaBoard - A pointer to a gameState with field filledCells that represents the amount of cells already filled in the game board of the current game.*/
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

void printChanges(int from, int to) {
	/*The function prints the changes made in the board by changing a cell from the value from to the value to.
	 * INPUT: int from - The previous value that was in the cell.
	 *        int to - the new value that is currently in the cell.*/
	if (from == 0)
		printf("_");
	else
		printf("%d", from);
	printf(" to ");
	if (to == 0)
		printf("_\n");
	else
		printf("%d\n", to);
}

void generateList(int toKeep, gameState *metaBoard) {
	/*The function generates and adds a move for the undo/redo list by looking at all the values added to the board, assuming the board was empty in the first place.
	 * INPUT: - int toKeep - The amount of cells that should be currently filled in the board, thus the number of changes happened in this move.
	 *          gameState *metaBoard - A pointer to a gameState with allocated board with valid values, we assume it was empty before the values were added.*/
	int i, j, filled = 0;
	int *moves = (int *) malloc(toKeep * 4 * sizeof(int));
	checkInitalize(moves, "malloc");
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[j][i].value != 0) {
				moves[filled * 4] = j;
				moves[filled * 4 + 1] = i;
				moves[filled * 4 + 2] = 0;
				moves[filled * 4 + 3] = metaBoard->gameBoard->board[j][i].value;
				filled++;
			}
		}
	}
	metaBoard->moves->currentMove = addNextMove(metaBoard->moves->currentMove, moves, toKeep);
	free(moves);
}

void startPuzzle(gameState *metaBoard, char *fileName, gameMode mode) {
	if ((mode == Edit) && (!fileName)) {/*Edit mode and file name wasn't provided*/
		freeBoard(metaBoard->gameBoard);
		metaBoard->mode = Edit;
		metaBoard->cols = metaBoard->gameBoard->cols = 3;
		metaBoard->rows = metaBoard->gameBoard->rows = 3;
		metaBoard->filledCells = 0;
		initalizeBoard(metaBoard->gameBoard);
		removeAllNext(metaBoard->moves->firstNode->next);/*Clear Undo/Redo list*/
		metaBoard->moves->currentMove = metaBoard->moves->firstNode;
		metaBoard->moves->currentMove->next = NULL;
		printBoard(metaBoard);
	} else
		sendToFill(metaBoard, fileName, mode);
}

void setBoard(int x, int y, int z, gameState *metaBoard, int set) {/*The set boolean parameter is used in order to not advance the undo/redo list when not needed eg. undo/redo*/
	int newMove[4];
	newMove[0] = x;
	newMove[1] = y;
	newMove[2] = metaBoard->gameBoard->board[x][y].value;
	newMove[3] = z;
	if (!metaBoard->gameBoard->board[x][y].fixed) {
		if (set)
			metaBoard->moves->currentMove = addNextMove(metaBoard->moves->currentMove, newMove, 1);
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

int validate(gameState *metaBoard) {
	int rows = metaBoard->gameBoard->rows;
	int cols = metaBoard->gameBoard->cols;
	int solved, amountFilled = 0;
	int* filled;
	double *sol = (double*) calloc(cols * rows * cols * rows * cols * rows, sizeof(double));
	checkInitalize(sol, "calloc");
	filled = findFilled(metaBoard, &amountFilled);
	solved = findSol(cols, rows, filled, amountFilled, sol);
	free(filled);
	free(sol);
	return solved;/*Solved will return -1 on Gurobi failure, 0 on unsolvable board and 1 if a solution was found*/
}

void generateBoard(int toFill, int toKeep, gameState *metaBoard) {
	int i, *filledCells, *values;
	int cols = metaBoard->cols, rows = metaBoard->rows;
	double *sol;
	sol = (double*) calloc(cols * rows * cols * rows * cols * rows, sizeof(double));
	checkInitalize(sol, "calloc");
	filledCells = (int *) malloc(sizeof(int) * toFill * 3);
	checkInitalize(filledCells, "malloc");
	values = (int *) malloc(sizeof(int) * cols * rows);
	checkInitalize(values, "malloc");
	for (i = 0; i < 1000; i++) {
		if (!tryFill(toFill, values, filledCells, metaBoard)) {
			eraseBoard(metaBoard->gameBoard);
		} else {
			if (findSol(cols, rows, filledCells, toFill, sol) > 0) {
				keepRandom(toKeep, metaBoard, sol);
				generateList(toKeep, metaBoard);/*Add the moves to undo/redo linked list*/
				printBoard(metaBoard);
				free(sol);
				free(filledCells);
				free(values);
				metaBoard->filledCells = toKeep;
				return;
			} else
				eraseBoard(metaBoard->gameBoard);
		}
	}
	eraseBoard(metaBoard->gameBoard);
	free(sol);
	free(filledCells);
	free(values);
	printf("Error: puzzle generator failed\n");
}

void undo(gameState *metaBoard) {
	int i;
	int *moves = metaBoard->moves->currentMove->change;
	if (metaBoard->moves->currentMove != metaBoard->moves->firstNode) {
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
	int *moves;
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

void saveBoard(gameState *metaBoard, char *fileName) {
	if (metaBoard->mode == Edit) {
		if (isErroneous(metaBoard)) {
			printf("Error: board contains erroneous values\n");
			return;
		} else if (!validate(metaBoard)) {
			printf("Error: board validation failed\n");
			return;
		}
	}
	saveToFile(metaBoard, fileName);
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
	else {
		sol = (double*) calloc(cols * rows * cols * rows * cols * rows, sizeof(double));
		checkInitalize(sol, "calloc");
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

void numOfSol(board *gameBoard) {
	int solutions = findNumSols(gameBoard);
	printf("Number of solutions:%d\n", solutions);
	if (solutions == 1)
		printf("This is a good board!\n");
	else if (solutions != 0)
		printf("The puzzle has more than 1 solution, try to edit further\n");
}

void autofill(gameState *metaBoard) {
	metaBoard->filledCells += fillSingleValues(metaBoard); /*Update amount of cells filled*/
	printBoard(metaBoard);
	checkWin(metaBoard);
}

void resetGame(gameState *metaBoard) {
	int *move;
	int i, j, counter;
	while (metaBoard->moves->currentMove != metaBoard->moves->firstNode) {
		move = metaBoard->moves->currentMove->change;
		counter = move[0];/*The amount of changes in the move*/
		for (i = 0; i < counter; i++) {/*Enter values to board and check the cell for erroneous conflicts*/
			metaBoard->gameBoard->board[move[i * 4 + 1]][move[i * 4 + 2]].value = move[i * 4 + 3];
		}
		metaBoard->moves->currentMove = metaBoard->moves->currentMove->prev;
	}
	counter = 0;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[j][i].value > 0)
				counter++;
			checkCell(j, i, metaBoard->gameBoard->board[j][i].value, 1, metaBoard->gameBoard);
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
