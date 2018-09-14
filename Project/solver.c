/*Source file which contains the functions that tries to solve or add values to the board without the use of ILP
* nextEmptyCell - a function that finds the next cell that is empty in the board,used by the findnumSols function,and returns 
* that cell index.
* checkSingleValue - a function used by the fillSingleValues function that checks if a value appears only once in a row,column and block
* of a cell provided to it as a parameter,and returns 0 or 1 accordingly
* fillSingleValues - a function ,used by the autofill function, that finds cells which only have one value that can be inserted to
* them without causing it to become erroneous
* fineNumSols - a function called when using the num_solutions command that returns the number of solutions the board has*/

#include <stdio.h>
#include <stdlib.h>
#include "gameStructs.h"
#include "linkedListFunc.h"
#include "mainAux.h"
#include "stackFunc.h"

int nextEmptyCell(int index, board *checkBoard) {
	/*The function recursively finds the next empty cell in board checkBoard, in case it exists (board not filled), starting search from input "index".
	 * The function assumes index is in the range of 0 to full board index.
	 *INPUT: int index - the cell we start the search from, can be between 0 and board length squared.
	 *		 board *checkBoard - a pointer to a valid board filled with 0 in empty places and values between 1 to board length in fixed cells or user inputed cells.
	 *OUTPUT: int representing index of the next empty cell counting from left to right, up to down numbering, or -1 if no such cell exists.*/
	int rows = checkBoard->rows;
	int cols = checkBoard->cols;
	if (index == rows * rows * cols * cols) {/*We reached to the end of the board*/
		return -1;
	}
	if (checkBoard->board[index % (cols * rows)][(int) (index / (rows * cols))].value == 0)/*Cell index is empty*/
		return index;
	return nextEmptyCell(index + 1, checkBoard);
}

int checkSingleValue(int x, int y, int z, gameState *metaBoard) {
	/*Checks if a value appears in a row/column/block of a cell.
	 INPUT: int x, y - The column and row of the cell that we want to check the value z on.
	        int z - The value we want to check in the <x,y> cell.
	        gameState *metaBoard - A valid gameState pointer with an allocated gameBoard with valid values.
	 OUTPUT: int indicating we could fill the cell with z (1) or we can't (0).*/
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check row*/
		if (metaBoard->gameBoard->board[i][y].value == z) {
			return 0;
		}
	}
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check column*/
		if (metaBoard->gameBoard->board[x][i].value == z) {
			return 0;
		}
	}
	for (i = (x / metaBoard->cols) * metaBoard->cols; i < (int) (x / metaBoard->cols) * metaBoard->cols + metaBoard->cols; i++) {
		for (j = (y / metaBoard->rows) * metaBoard->rows; j < (int) (y / metaBoard->rows) * metaBoard->rows + metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[i][j].value == z) {
				return 0;
			}
		}
	}
	return 1;
}

int fillSingleValues(gameState *metaBoard) {
	int i, j, k, counter = 0, posValues;
	int *moves = (int *) malloc(0);
	checkInitalize(moves, "malloc");
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[j][i].value != 0)
				continue;
			posValues = 0;
			for (k = 1; k <= metaBoard->rows * metaBoard->cols; k++) {/*Check the possible values to insert to the <i,j> cell*/
				if (checkSingleValue(j, i, k, metaBoard)) {
					if (posValues == 0)
						posValues = k;
					else {
						posValues = 0;
						break;
					}
				}
			}
			if (posValues == 0)/*Couldn't find a value to put in the cell or we had more than one value to put in the cell*/
				continue;
			else {/*This cell only had a single value that we could enter it, so we add it to the moves array!*/
				counter++;
				moves = realloc(moves, sizeof(int) * counter * 4);/*Reallocate extra space*/
				checkInitalize(moves, "realloc");
				moves[(counter - 1) * 4] = j;/*Adds the change to the new move array*/
				moves[(counter - 1) * 4 + 1] = i;
				moves[(counter - 1) * 4 + 2] = 0;
				moves[(counter - 1) * 4 + 3] = posValues;
				printf("Cell <%d,%d> set to %d\n", j + 1, i + 1, posValues);
			}
		}
	}
	if (counter)/*Update the list only if any changes were made*/
		metaBoard->moves->currentMove = addNextMove(metaBoard->moves->currentMove, moves, counter);/*Update linked list of moves*/
	for (i = 0; i < counter; i++) {/*Enter values to board and check the cell for erroneous conflicts*/
		metaBoard->gameBoard->board[moves[i * 4]][moves[i * 4 + 1]].value = moves[i * 4 + 3];
		checkCell(moves[i * 4], moves[i * 4 + 1], moves[i * 4 + 3], 1, metaBoard->gameBoard);
	}
	free(moves);
	return counter;
}

int findNumSols(board *gameBoard) {
	int x = 0, y = 0, i = 1, index = 0;
	int solutions = 0, rows = gameBoard->rows, cols = gameBoard->cols;
	int found = 1;
	item temp;
	stackPointer backStack;
	backStack.maxSize = cols * rows;
	backStack.stack = calloc(backStack.maxSize, sizeof(item));
	checkInitalize(backStack.stack, "calloc");
	backStack.size = 0;
	do {
		if (found) {/*We try to find a new cell to fill*/
			index = nextEmptyCell(index, gameBoard);/*Find next Empty Cell*/
			if (index == -1) {/*We reached the end of the board so we found a valid solution*/
				solutions++;
				temp = pop(&backStack);/*Pop the last cell that we have filled*/
				i = gameBoard->board[x][y].value + 1;/*Try bigger values for this cell*/
				x = temp.index % (cols * rows);
				y = temp.index / (rows * cols);
			} else {
				x = index % (cols * rows);/*Extract the column of the cell by index*/
				y = index / (rows * cols);/*Extract the row of the cell by index*/
				index++;
				i = 1;/*Try values from 1 since it's a new cell we try to fill*/
			}
		}
		/*If we didn't enter if, we backtracked so x, y and i were updated already for the last cell we entered to the stack*/
		found = 0;
		for (; i < rows * cols + 1; i++) {
			checkCell(x, y, i, 0, gameBoard);
			if (!gameBoard->board[x][y].error) {
				gameBoard->board[x][y].value = i;
				temp.index = x + y * rows * cols;
				push(temp, &backStack);
				found = 1;
				temp = *(backStack.stack + backStack.size - 1);
				break;/*We found a fitting value to this cell, we move to next cell*/
			}
		}
		if (!found) {
			gameBoard->board[x][y].value = 0;/*We need to reverse the cell back to empty*/
			gameBoard->board[x][y].error = 0;
			if (backStack.size > 0) {
				temp = pop(&backStack);
				index = temp.index;/*We backtrack so we try bigger values for the last cell we entered*/
				x = index % (cols * rows);
				y = index / (rows * cols);
				i = gameBoard->board[x][y].value + 1;/*Try bigger values for this cell*/
			}
		}
	} while ((backStack.size > 0) || (i < (cols * rows) + 1));
	gameBoard->board[x][y].value = 0;/*We reverse the first cell we entered back to empty*/
	gameBoard->board[x][y].error = 0;
	free(backStack.stack);
	return solutions;
}
