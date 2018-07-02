#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "gameStructs.h"
#include "linkedListFunc.h"

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

void solver(board *tmpBoard, int *indexCounter) {
	int x, y, i;
	indexCounter[0] = nextEmptyCell(indexCounter[0], tmpBoard);/*Find next Empty Cell*/
	if (indexCounter[0] == -1) {/*We reached the end of the board so we found a valid solution*/
		indexCounter[1]++;
	} else {
		x = indexCounter[0] % (tmpBoard->cols * tmpBoard->rows);/*Extract the column of the cell by index*/
		y = (int) (indexCounter[0] / (tmpBoard->rows * tmpBoard->cols));/*Extract the row of the cell by index*/
		indexCounter[0]++;
		for (i = 1; i < tmpBoard->rows * tmpBoard->cols + 1; i++) {
			if (checkCell(x, y, i, tmpBoard)) {
				tmpBoard->board[x][y].value = i;
				solver(tmpBoard, indexCounter);/*Current board is a valid solution*/
			}
		}
		tmpBoard->board[x][y].value = 0;/*We need to reverse the cell back to empty*/
	}
}

int checkSingleValue(int x, int y, int z, gameState *metaBoard) {
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check column*/
		if (metaBoard->gameBoard->board[i][y].value == z) {
			return 0;
		}
	}
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check row*/
		if (metaBoard->gameBoard->board[x][i].value == z) {
			return 0;
		}
	}
	for (i = (x / metaBoard->rows) * metaBoard->rows;
			i < (int) (x / metaBoard->rows) * metaBoard->rows + metaBoard->rows;
			i++) {
		for (j = (y / metaBoard->cols) * metaBoard->cols;
				j
						< (int) (y / metaBoard->cols) * metaBoard->cols
								+ metaBoard->cols; j++) {
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
	for (i = 0; i < metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->rows; j++) {
			posValues = 0;
			for (k = 1; i <= metaBoard->rows * metaBoard->cols; i++) {/*Check the possible values to insert to the <i,j> cell*/
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
	metaBoard->moves->currentMove = addNextMove(metaBoard->moves->currentMove,
			moves, counter);/*Update linked list of moves*/
	for (i = 0; i < counter; i++) {/*Enter values to board and check the cell for erroneous conflicts*/
		metaBoard->gameBoard->board[moves[i * 4]][moves[i * 4 + 1]].value = moves[i
				* 4 + 3];
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
