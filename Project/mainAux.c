/*Source file which contains auxiliary functions that are shared between different modules
* checkInitialize - A function that checks if the data we tried to allocate did allocate
* freeBoard - A function used when exiting that frees the board
* eraseBoard - A function that resets the board so it will be empty,nothing fixed and no cell is erroneous
* initializeBoard - A function that at the start of the game allocates space for the board
* printBoard - A function that prints the board
* checkCell - A function that checks if there are erroneous values in the row col and block of the cell that we provide
* isErroneous - A function that checks if the board contains an erroneous value in a cell*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameStructs.h"

void checkInitalize(void *pointer, char *cmd) {
	if (pointer == NULL) {
		printf("Error: %s has failed\n", cmd);
		exit(0);
	}
}

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

void initalizeBoard(board *newBoard) {
	/*The function allocates the memory needed for the board newBoard according to the values in it's rows and cols fields, as a 2-D array of type cell.
	 *INPUT: board *newBoard - A pointer to a board that has values in it's rows and cols fields, and haven't had any memory allocated to it yet.*/
	int i;
	newBoard->board = (cell**) calloc(newBoard->rows * newBoard->cols, sizeof(cell *));
	checkInitalize(newBoard->board, "calloc");
	for (i = 0; i < newBoard->rows * newBoard->cols; i++) {
		newBoard->board[i] = (cell*) calloc(newBoard->rows * newBoard->cols, sizeof(cell));
		checkInitalize(newBoard->board[i], "calloc");
	}
	eraseBoard(newBoard);
}

void printBoard(gameState *metaBoard) {
	int i, j;
	board *playerBoard = metaBoard->gameBoard;
	for (i = 0; i < playerBoard->cols * playerBoard->rows; i++) {
		if (i % playerBoard->rows == 0) {
			for (j = 0; j < playerBoard->rows * playerBoard->cols * 4 + playerBoard->rows + 1; j++) {
				printf("-");
			}
			printf("\n");
		}
		for (j = 0; j < playerBoard->rows * playerBoard->cols; j++) {
			if (j == 0) {
				printf("|");
			}
			printf(" ");
			if (playerBoard->board[j][i].value == 0) {
				printf("   ");
			} else {
				printf("%2d", playerBoard->board[j][i].value);
				if (playerBoard->board[j][i].fixed)
					printf(".");
				else if ((playerBoard->board[j][i].error) && ((metaBoard->markError) || (metaBoard->mode == Edit)))
					printf("*");
				else
					printf(" ");
			}
			if (j % playerBoard->cols == playerBoard->cols - 1)
				printf("|");
		}
		printf("\n");
	}
	for (j = 0; j < playerBoard->rows * playerBoard->cols * 4 + playerBoard->rows + 1; j++) {
		printf("-");
	}
	printf("\n");
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
