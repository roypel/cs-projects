#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameStructs.h"
#include "linkedListFunc.h"
#include "solver.h"
#include "game.h"

void fillBoard(gameState *metaBoard, FILE* ifp) {
	int input, i, j, filled = 0;
	char *c, string[4] = { 0 };/*USING THE 5*5 LIMITATION, MAYBE USE CALLOC WITH log_10 instead*/
	/*c used to check each char in a cell, string used to read a cell (number + fixed + \0)*/
	if (metaBoard->gameBoard)
		freeBoard(metaBoard->gameBoard);
	fscanf(ifp, "%d", &input); /*Read block size*/
	metaBoard->gameBoard->cols = metaBoard->cols = input;
	filled += input;
	fscanf(ifp, "%d", &input);
	metaBoard->gameBoard->rows = metaBoard->rows = input;
	filled *= input;
	filled *= filled; /*Number of possible filled cells is block size squared*/
	removeAllNext(metaBoard->moves->firstNode->next);/*Clear Undo/Redo list*/
	initalizeBoard(metaBoard->gameBoard);
	for (i = 0; i < metaBoard->rows * metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			fscanf(ifp, "%s", string); /*Read next cell*/
			c = string; /*Questionable implementation, maybe can replace string with c*/
			if (*c == '0') {/*Cell is empty, filled decrease and not fixed (default 0)*/
				filled--;
			} else {
				while (c != '\0') {/*Read until end of cell*/
					if ((*c == '.') && (metaBoard->mode == Solve)) {/*Cell is fixed in Solve mode (in edit everything is unfixed)*/
						metaBoard->gameBoard->board[i][j].fixed = 1;
					} else {
						metaBoard->gameBoard->board[i][j].value *= 10;/*Insert another digit*/
						metaBoard->gameBoard->board[i][j].value += (*c - '0');
					}
					c++;
				}
			}
		}
	}
}

void saveFile(gameState *metaBoard, char *fileName) {
	FILE *ifp;
	int i, j, indexCounter[2] = { 0 };/*USED ONLY TEMPORARY NTIL WE DO VALIDATE ILP*/
	if (metaBoard->mode == Edit) {
		if (isErroneous(metaBoard)) {
			printf("Error: board contains erroneous values\n");
			return;
		} else {
			solver(metaBoard->gameBoard, indexCounter);
			if (!indexCounter[1]) {
				printf("Error: board validation failed\n");
				return;
			}
		}
	}
	ifp = fopen(fileName, "w");
	if (!ifp) {
		printf("Error: File cannot be created or modified\n");
		return;
	}
	fprintf(ifp, "%d ", metaBoard->gameBoard->cols);
	fprintf(ifp, "%d\n", metaBoard->gameBoard->rows);
	for (i = 0; i < metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->rows; j++) {
			fprintf(ifp, "%d", metaBoard->gameBoard->board[i][j].value);
			if ((metaBoard->mode == Edit)
					|| (metaBoard->gameBoard->board[i][j].fixed))
				fprintf(ifp, "%c", '.');
			fprintf(ifp, " ");
		}
		fprintf(ifp, "\n");
	}
	fclose(ifp);
	printf("Saved to: %s\n", fileName);
}

void sendToFill(gameState *metaBoard, char *fileName) {
	FILE *ifp;
	ifp = fopen(fileName, "r");
	if (!ifp) {
		if (metaBoard->mode == Solve) {/*Solve mode and file can't be opened or doesn't exist*/
			printf("Error: File doesn't exist or cannot be opened\n");
			return;
		}
		if (!fileName) {/*Edit mode and file name wasn't provided*/
			if (metaBoard->mode == Init) {
				freeBoard(metaBoard->gameBoard);
				removeAllNext(metaBoard->moves->firstNode->next);/*Clear Undo/Redo list*/
			}
			metaBoard->cols = 3;
			metaBoard->rows = 3;
			metaBoard->gameBoard->cols = 3;
			metaBoard->gameBoard->rows = 3;
			metaBoard->filledCells = 0;
			initalizeBoard(metaBoard->gameBoard);
			return;
		}
		printf("Error: File cannot be opened\n");/*Edit mode and file can't be opened or doesn't exist*/
		return;
	}
	fillBoard(metaBoard, ifp);
}

