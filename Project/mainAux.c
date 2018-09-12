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

void checkInitalize(void *pointer, char *cmd) {
	if (pointer == NULL) {
		printf("Error: %s has failed\n", cmd);
		exit(0);
	}
}
