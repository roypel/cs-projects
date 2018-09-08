#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameStructs.h"

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

void printChanges(int from, int to) {
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

void checkInitalize(void *pointer, char *cmd) {
	if (pointer == NULL) {
		printf("Error: %s has failed\n", cmd);
		exit(0);
	}
}
