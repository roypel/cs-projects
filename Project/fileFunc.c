#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameStructs.h"
#include "linkedListFunc.h"
#include "game.h"
#include "MainAux.h"

void checkScan(int scan) {
	if (scan == EOF) {
		printf("Error: fscanf has failed\n");
		exit(0);
	}
}

void fillBoard(gameState *metaBoard, FILE* ifp) {
	int input, i, j, k, filled = 0;
	char *c, string[4] = { 0 };/*USING THE 5*5 LIMITATION, MAYBE USE CALLOC WITH log_10 instead*/
	/*c used to check each char in a cell, string used to read a cell (number + fixed + \0)*/
	if (metaBoard->gameBoard->board)
		freeBoard(metaBoard->gameBoard);
	checkScan(fscanf(ifp, "%d", &input));/*Read block size*/
	metaBoard->gameBoard->cols = metaBoard->cols = input;
	filled += input;
	checkScan(fscanf(ifp, "%d", &input));
	metaBoard->gameBoard->rows = metaBoard->rows = input;
	filled *= input;
	filled *= filled; /*Number of possible filled cells is block size squared*/
	removeAllNext(metaBoard->moves->firstNode->next);/*Clear Undo/Redo list*/
	metaBoard->moves->currentMove = metaBoard->moves->firstNode;
	metaBoard->moves->currentMove->next = NULL;
	initalizeBoard(metaBoard->gameBoard);
	for (i = 0; i < metaBoard->rows * metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			checkScan(fscanf(ifp, "%s", string)); /*Read next cell*/
			c = string; /*Questionable implementation, maybe can replace string with c*/
			if (*c == '0') {/*Cell is empty, filled decrease and not fixed (default 0)*/
				filled--;
				metaBoard->gameBoard->board[j][i].error = 0;
				metaBoard->gameBoard->board[j][i].fixed = 0;
			} else {
				for (k = 0; k < (int) strlen(c); k++) {
					/*while (c != '\0') {Read until end of cell*/
					if (c[k] == '.') {
						if (metaBoard->mode == Solve) /*Cell is fixed in Solve mode (in edit everything is unfixed)*/
							metaBoard->gameBoard->board[j][i].fixed = 1;
					} else {
						metaBoard->gameBoard->board[j][i].value *= 10;/*Insert another digit*/
						metaBoard->gameBoard->board[j][i].value += (c[k] - '0');
					}
				}
				checkCell(j, i, metaBoard->gameBoard->board[j][i].value, 1,
						metaBoard->gameBoard);
			}
		}
	}
	metaBoard->filledCells = filled;
	fclose(ifp);
	printBoard(metaBoard);
}

void saveFile(gameState *metaBoard, char *fileName) {
	FILE *ifp;
	int i, j;
	if (metaBoard->mode == Edit) {
		if (isErroneous(metaBoard)) {
			printf("Error: board contains erroneous values\n");
			return;
		} else if (!validate(metaBoard)) {
			printf("Error: board validation failed\n");
			return;
		}
	}
	ifp = fopen(fileName, "w");
	if (!ifp) {
		printf("Error: File cannot be created or modified\n");
		return;
	}
	fprintf(ifp, "%d ", metaBoard->gameBoard->cols);
	fprintf(ifp, "%d\n", metaBoard->gameBoard->rows);
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			fprintf(ifp, "%d", metaBoard->gameBoard->board[j][i].value);
			if ((metaBoard->mode == Edit)
					|| (metaBoard->gameBoard->board[j][i].fixed))
				fprintf(ifp, "%c", '.');
			fprintf(ifp, " ");
		}
		fprintf(ifp, "\n");
	}
	fclose(ifp);
	printf("Saved to: %s\n", fileName);
}

void sendToFill(gameState *metaBoard, char *fileName, gameMode mode) {
	FILE *ifp;
	if ((mode == Edit) && (!fileName)) {/*Edit mode and file name wasn't provided*/
		if (metaBoard->mode == Init) {
			freeBoard(metaBoard->gameBoard);
			removeAllNext(metaBoard->moves->firstNode->next);/*Clear Undo/Redo list*/
			metaBoard->moves->currentMove = metaBoard->moves->firstNode;
			metaBoard->moves->currentMove->next = NULL;
		}
		metaBoard->mode = Edit;
		metaBoard->cols = 3;
		metaBoard->rows = 3;
		metaBoard->gameBoard->cols = 3;
		metaBoard->gameBoard->rows = 3;
		metaBoard->filledCells = 0;
		initalizeBoard(metaBoard->gameBoard);
		printBoard(metaBoard);
		return;
	}
	ifp = fopen(fileName, "r");
	if (!ifp) {
		if (mode == Solve) {/*Solve mode and file can't be opened or doesn't exist*/
			printf("Error: File doesn't exist or cannot be opened\n");
			return;
		}
		printf("Error: File cannot be opened\n");/*Edit mode and file can't be opened or doesn't exist*/
		return;
	}
	metaBoard->mode = mode;
	fillBoard(metaBoard, ifp);
}
