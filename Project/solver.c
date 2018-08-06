#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "gameStructs.h"
#include "linkedListFunc.h"
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
	if (checkBoard->board[index % (cols * rows)][(int) (index / (rows * cols))].value
			== 0)/*Cell index is empty*/
		return index;
	return nextEmptyCell(index + 1, checkBoard);
}

int solver(board *gameBoard) {
	int x, y, i, index = 0;
	int solutions = 0;
	int found = 1;
	item temp;
	stackPointer backStack;
	backStack.maxSize = gameBoard->cols * gameBoard->rows;
	backStack.stack = calloc(backStack.maxSize, sizeof(item));
	if (backStack.stack == NULL) {
				printf("Error: calloc has failed\n");
				exit(0);
			}
	backStack.size = 0;
	do {
		if (found) {/*We try to find a new cell to fill*/
			index = nextEmptyCell(index, gameBoard);/*Find next Empty Cell*/
			if (index == -1) {/*We reached the end of the board so we found a valid solution*/
				solutions++;
				temp = pop(&backStack);/*Pop the last cell that we have filled*/
				i = temp.val + 1;/*Try bigger values for this cell*/
				x = temp.col;
				y = temp.row;
			} else {
				x = index % (gameBoard->cols * gameBoard->rows);/*Extract the column of the cell by index*/
				y = index / (gameBoard->rows * gameBoard->cols);/*Extract the row of the cell by index*/
				index++;
				i = 1;/*Try values from 1 since it's a new cell we try to fill*/
			}
		} else {/*We backtracked so we try bigger values for this cell*/
			i = temp.val + 1;/*Try bigger values for this cell*/
			x = temp.col;
			y = temp.row;
		}
		found = 0;
		for (; i < gameBoard->rows * gameBoard->cols + 1; i++) {
			checkCell(x, y, i, gameBoard);
			if (!gameBoard->board[x][y].error) {
				printf("wazzup%d %d %d\n", x , y ,i);
				gameBoard->board[x][y].value = i;
				temp.col = x;
				temp.row = y;
				temp.val = i;
				push(temp, &backStack);
				found = 1;
				temp = *(backStack.stack + (sizeof(item) * (backStack.size-1)));
				printf("col %d row %d val %d\n", temp.col, temp.row, temp.val);
				break;/*We found a fitting value to this cell, we move to next cell*/
			}
		}
		if (!found) {
			gameBoard->board[x][y].value = 0;/*We need to reverse the cell back to empty*/
			temp = pop(&backStack);
		}
	} while (backStack.size != 0);
	free(backStack.stack);
	return solutions;
}

int checkSingleValue(int x, int y, int z, gameState *metaBoard) {
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
	for (i = (x / metaBoard->cols) * metaBoard->cols;
			i < (int) (x / metaBoard->cols) * metaBoard->cols + metaBoard->cols;
			i++) {
		for (j = (y / metaBoard->rows) * metaBoard->rows;
				j
						< (int) (y / metaBoard->rows) * metaBoard->rows
								+ metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[i][j].value == z) {
				return 0;
			}
		}
	}
	return 1;
}

void autoFill(gameState *metaBoard) {
	int i, j, k, counter = 0, posValues;
	int * moves = (int *) malloc(0);
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[i][j].value != 0)
				continue;
			posValues = 0;
			for (k = 1; k <= metaBoard->rows * metaBoard->cols; k++) {/*Check the possible values to insert to the <i,j> cell*/
				if (checkSingleValue(i, j, k, metaBoard)) {
					if (posValues == 0)
						posValues = k;
					else {
						posValues = 0;
						break;
					}
				}
			}
			if (posValues == 0)/*Didn't found a single value to enter*/
				continue;
			else {
				counter++;
				moves = realloc(moves, sizeof(int) * counter * 4);/*Reallocate extra space*/
				moves[(counter - 1) * 4] = i;
				moves[(counter - 1) * 4 + 1] = j;
				moves[(counter - 1) * 4 + 2] = 0;
				moves[(counter - 1) * 4 + 3] = posValues;
			}
		}
	}
	if (counter)/*Update the list only if any changes were made*/
		metaBoard->moves->currentMove = addNextMove(
				metaBoard->moves->currentMove, moves, counter);/*Update linked list of moves*/
	for (i = 0; i < counter; i++) {/*Enter values to board and check the cell for erroneous conflicts*/
		metaBoard->gameBoard->board[moves[i * 4]][moves[i * 4 + 1]].value =
				moves[i * 4 + 3];
		checkCell(moves[i * 4], moves[i * 4 + 1], moves[i * 4 + 3],
				metaBoard->gameBoard);
	}
}

void hinter(gameState *metaBoard) {
	int col, row;
	int hints = metaBoard->filledCells;
	while (hints) {/*As long as we need to add more hints*/
		col = rand() % (metaBoard->cols * metaBoard->rows);
		row = rand() % (metaBoard->cols * metaBoard->rows);
		if (!metaBoard->gameBoard->board[col][row].fixed) {
			metaBoard->gameBoard->board[col][row].fixed = 1;
			hints--;
		}
	}
}
