/*Source file which contains auxiliary functions that we use in different modules that don't directly relate to the game commands*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameStructs.h"

void freeBoard(board *freeBird) {
	int i;
	for (i = 0; i < freeBird->rows * freeBird->cols; i++) {
		free((freeBird->board)[i]);
	}
	free(freeBird->board);
}

void initalizeBoard(board *newBoard) {
	int i;
	newBoard->board = (cell**) calloc(newBoard->rows * newBoard->cols, sizeof(cell *));
	checkInitalize(newBoard->board, "calloc");
	for (i = 0; i < newBoard->rows * newBoard->cols; i++) {
		newBoard->board[i] = (cell*) calloc(newBoard->rows * newBoard->cols, sizeof(cell));
		checkInitalize(newBoard->board[i], "calloc");
	}
	eraseBoard(newBoard);
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
		for (i = (x / check->cols) * check->cols; i < (int) (x / check->cols) * check->cols + check->cols; i++) {
			for (j = (y / check->rows) * check->rows; j < (int) (y / check->rows) * check->rows + check->rows; j++) {/*Check block*/
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
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[i][j].error == 1)
				return 1;
		}
	}
	return 0;
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

void checkInitalize(void *pointer, char *cmd) {
	if (pointer == NULL) {
		printf("Error: %s has failed\n", cmd);
		exit(0);
	}
}
