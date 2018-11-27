#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "gameStructs.h"

int nextEmptyCell(int index, board *checkBoard) {
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

int solver(board *tmpBoard, int index) {
	int x, y, i;
	index = nextEmptyCell(index, tmpBoard);/*Find next Empty Cell*/
	if (index == -1) {/*We reached the end of the board so we found a valid solution*/
		return 1;
	}
	x = index % (tmpBoard->cols * tmpBoard->rows);/*Extract the column of the cell by index*/
	y = (int) (index / (tmpBoard->rows * tmpBoard->cols));/*Extract the row of the cell by index*/
	for (i = 1; i < tmpBoard->rows * tmpBoard->cols + 1; i++) {
		if (checkCell(x, y, i, tmpBoard)) {
			tmpBoard->board[x][y].value = i;
			if (solver(tmpBoard, index + 1))/*Current board is a valid solution*/
				return 1;
			tmpBoard->board[x][y].value = 0;/*Current board isn't valid, need to increase input on cell*/
		}
	}
	return 0;/*Couldn't find a valid solution for cell*/
}

void builder(board *buildBoard, int x, int y) {
	int i, nextTry;
	int *posValues;
	if (y != buildBoard->rows * buildBoard->cols) {
		posValues = calloc(buildBoard->rows * buildBoard->cols + 1,
				sizeof(int));/*Possible values for cell <x,y>*/
		if (posValues == NULL) {
			printf("Error: calloc has failed\n");
			exit(0);
		}
		for (i = 1; i <= buildBoard->rows * buildBoard->cols; i++) {
			if (checkCell(x, y, i, buildBoard)) {
				posValues[0]++;/*Amount of possible values for cell <x,y>*/
				posValues[posValues[0]] = i;
			}
		}
		while (posValues[0] != 0) {/*There are still possible values to insert to cell <x,y>*/
			if (posValues[0] == 1) {/*Only one possible value to insert, don't use random*/
				nextTry = 1;
			} else {
				nextTry = (rand() % posValues[0]) + 1;/*The index of the next random try*/
			}
			buildBoard->board[x][y].value = posValues[nextTry];
			for (i = nextTry; i < posValues[0]; i++) {/*Shift left the possible values for continuity of the array*/
				posValues[i] = posValues[i + 1];
			}
			posValues[0]--;/*Update the remaining possible values*/
			if (x == buildBoard->rows * buildBoard->cols - 1)
				builder(buildBoard, 0, y + 1);/*Recursive call for next new row (Rightmost column,
				 we need to move to the leftmost column of the next row)*/
			else
				builder(buildBoard, x + 1, y);/*Recursive call for next right cell*/
			if (buildBoard->board[buildBoard->rows * buildBoard->cols - 1][buildBoard->rows
					* buildBoard->cols - 1].value != 0)/*Board is full, no need for further tries*/
				break;
			buildBoard->board[x][y].value = 0;
		}
		free(posValues);
	}
}

void hinter(gameState *metaBoard) {
	int x, y;
	int hints = metaBoard->filledCells;
	while (hints) {/*As long as we need to add more hints*/
		x = rand() % (metaBoard->cols * metaBoard->rows);
		y = rand() % (metaBoard->cols * metaBoard->rows);
		if (!metaBoard->gameBoard->board[x][y].fixed) {
			metaBoard->gameBoard->board[x][y].fixed = 1;
			hints--;
		}
	}
}
