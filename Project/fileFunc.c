#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameStructs.h"
#include "linkedListFunc.h"
#include "game.h"
#include "mainAux.h"

void checkScan(int scan) {
	/* The function checks if the input "scan" is a valid input from the function fscanf, or we got an error / reached EOF.
	 * If "scan" indicates an error/EOF, the function prints an error message and exits the program.
	 * INPUT: int scan - an integer returned from the function fscanf.*/
	if (scan == EOF) {
		printf("Error: fscanf has failed\n");
		exit(0);
	}
}

int checkSize(int cols, int rows) {
	/*The function calculates the maximum possible size of a string holding information for a cell in the board.
	 * Calculated by maximum amount of digits + 1 for '.' or '*' + 1 for '\0'.
	 * INPUT: int cols, rows - The */
	int size = 0, num = cols * rows;
	while (num != 0) {
		num /= 10;
		size++;
	}
	size += 2;/*For '.' or '*' and '\0'.*/
	printf("%d\n", size);
	return size;
}

void fillBoard(gameState *metaBoard, FILE *ifp) {
	/* The function receives a pointer to an open file ifp, assuming it's a valid and correctly formatted sudoku board, and a pointer to the current
	 * gameState metaBoard, and fills the current game board according to the file format: first number is the number of rows in a block, second number
	 * is the number of columns in a block, and the rest of the file contains the values to insert in each cell, and a '.' to indicate a fixed cell.
	 * INPUT: gameState *metaBoard - A valid gameState pointer that keeps information for the current game. Will be initialized and filled with a
	 * new gameBoard with values from the board in the file, an empty undo/redo list, and any information needed to keep the new gameState.
	 *        FILE *ifp - An open file, containing information of a valid sudoku game board.*/
	int input, i, j, k, filled = 0;
	char *cell = {0};
	if (metaBoard->gameBoard->board)/*Free memory from previous game board, if it exists*/
		freeBoard(metaBoard->gameBoard);
	checkScan(fscanf(ifp, "%d", &input));/*Read block size*/
	metaBoard->gameBoard->rows = metaBoard->rows = input;
	filled += input;
	checkScan(fscanf(ifp, "%d", &input));
	metaBoard->gameBoard->cols = metaBoard->cols = input;
	filled *= input;
	filled *= filled; /*Number of possible filled cells is block size squared*/
	removeAllNext(metaBoard->moves->firstNode->next);/*Clear Undo/Redo list*/
	metaBoard->moves->currentMove = metaBoard->moves->firstNode;
	metaBoard->moves->currentMove->next = NULL;
	initalizeBoard(metaBoard->gameBoard);
	cell = (char *) calloc(checkSize(metaBoard->cols, metaBoard->rows), sizeof(char));
	checkInitalize(cell, "calloc");
	for (i = 0; i < metaBoard->rows * metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			checkScan(fscanf(ifp, "%s", cell)); /*Read next cell*/
			if (*cell == '0') {/*Cell is empty, filled decrease and not fixed (default 0)*/
				filled--;
				metaBoard->gameBoard->board[j][i].error = 0;
				metaBoard->gameBoard->board[j][i].fixed = 0;
			} else {
				for (k = 0; k < (int) strlen(cell); k++) {
					if (cell[k] == '.') {
						if (metaBoard->mode == Solve) /*Cell is fixed in Solve mode (in edit everything is unfixed)*/
							metaBoard->gameBoard->board[j][i].fixed = 1;
					} else {
						metaBoard->gameBoard->board[j][i].value *= 10;/*Insert another digit*/
						metaBoard->gameBoard->board[j][i].value += (cell[k] - '0');
					}
				}
				checkCell(j, i, metaBoard->gameBoard->board[j][i].value, 1, metaBoard->gameBoard);
			}
		}
	}
	metaBoard->filledCells = filled;
	free(cell);
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
	fprintf(ifp, "%d ", metaBoard->gameBoard->rows);
	fprintf(ifp, "%d\n", metaBoard->gameBoard->cols);
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			fprintf(ifp, "%d", metaBoard->gameBoard->board[j][i].value);
			if ((metaBoard->gameBoard->board[j][i].value != 0) && ((metaBoard->mode == Edit) || (metaBoard->gameBoard->board[j][i].fixed)))/*Add '.' if we are in Edit mode or cell is fixed and it has a value (not 0)*/
				fprintf(ifp, "%c", '.');
			if (j != metaBoard->cols * metaBoard->rows - 1)/*Don't insert space on last cell in line*/
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
		freeBoard(metaBoard->gameBoard);
		metaBoard->mode = Edit;
		metaBoard->cols = metaBoard->gameBoard->cols = 3;
		metaBoard->rows = metaBoard->gameBoard->rows = 3;
		metaBoard->filledCells = 0;
		initalizeBoard(metaBoard->gameBoard);
		removeAllNext(metaBoard->moves->firstNode->next);/*Clear Undo/Redo list*/
		metaBoard->moves->currentMove = metaBoard->moves->firstNode;
		metaBoard->moves->currentMove->next = NULL;
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
