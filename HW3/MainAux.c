#include <stdio.h>
#include <string.h>
#include "gameStructs.h"

void printBoard(board *playerBoard) {
	int i, j;
	for (i = 0; i < playerBoard->cols * playerBoard->rows; i++) {
		if (i % playerBoard->rows == 0) {
			for (j = 0; j < playerBoard->rows * playerBoard->cols * 3 + 2 * playerBoard->cols + 1; j++) {
				printf("-");
			}
			printf("\n");
		}
		for (j = 0; j < playerBoard->rows * playerBoard->cols; j++) {
			if (j == 0) {
				printf("|");
			}
			if (playerBoard->board[j][i].fixed)
				printf(" .%d", playerBoard->board[j][i].value);
			else {
				printf("  ");
				if (playerBoard->board[j][i].value == 0)
					printf(" ");
				else
					printf("%d", playerBoard->board[j][i].value);
			}
			if (j % playerBoard->cols == playerBoard->cols - 1)
				printf(" |");
		}
		printf("\n");
	}
	for (j = 0; j < playerBoard->rows * playerBoard->cols * 3 + 2 * playerBoard->cols + 1; j++) {
		printf("-");
	}
	printf("\n");
}

int getSeed(char *input){
	int seed = 0, i, multiplier = 1;
	for (i = (int)strlen(input)-1; i >= 0; i--) {
		seed += (input[i]-48) * multiplier;
		multiplier *= 10;
	}
	return seed;
}

void checkWin(gameState *metaBoard) {
	int cols = metaBoard->gameBoard->cols;
	int rows = metaBoard->gameBoard->rows;
	if (metaBoard->filledCells == cols * cols * rows * rows) {
		printf("Puzzle solved successfully\n");

	}
}
