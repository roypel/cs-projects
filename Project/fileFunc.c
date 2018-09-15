/* Source file which contains functions that are used in order to read from files containing boards or creating new files containing boards.
 * The module will be used as the only way to open files for reading or writing in the program. Includes the following functions:
 * checkScan - A small helper function used to check if the input that the function fcsanf red was valid or not.
 * checkSize - A function used to calculate the maximum possible size of characters used to represent a cell in the board, depending on the board size.
 * fillBoard - A function that reads a file containing a valid game board (i.e. values between 0-N, board might not have a valid solution)
 *             and fills the relevant game structures so a puzzle may be edited or solved from the file given.
 * saveToFile - A function used to save the state of the current board into a file for future use. The first two numbers represent the
 *              block size (rows X columns) and afterwards the values of each cell will be stored separately, adding information for fixed cells with a '.'.
 * sendToFill - A function used to try and open a file before we read information from it, and if the file was opened successfully, changes the game mode and sends the file to fillBoard.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameStructs.h"
#include "linkedListFunc.h"
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
	size += 2;/*For '.' or '*', and '\0'.*/
	return size;
}

void fillBoard(gameState *metaBoard, FILE *ifp) {
	/* The function receives a pointer to an open file ifp, assuming it's a valid and correctly formatted sudoku board, and a pointer to the current
	 * gameState metaBoard, and fills the current game board according to the file format: first number is the number of rows in a block, second number
	 * is the number of columns in a block, and the rest of the file contains the values to insert in each cell, and a '.' to indicate a fixed cell.
	 * INPUT: gameState *metaBoard - A valid gameState pointer that keeps information for the current game. Will be initialized and filled with a
	 * new gameBoard with values from the board in the file, an empty undo/redo list, and any information needed to keep the new gameState.
	 *        FILE *ifp - An open file, containing information of a valid sudoku game board.*/
	int input, i, j, filled = 0, size;
	char *cell;
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
			size = 0;/*Will keep amount of characters in cell*/
			if (*cell == '0') {/*Cell is empty, filled decrease and not fixed (default 0)*/
				filled--;
				metaBoard->gameBoard->board[j][i].error = 0;
				metaBoard->gameBoard->board[j][i].fixed = 0;
			} else {
				while (*cell != '\0') {
					size++;
					if (*cell == '.') {
						if (metaBoard->mode == Solve) /*Cell is fixed in Solve mode (in edit everything is unfixed)*/
							metaBoard->gameBoard->board[j][i].fixed = 1;
					} else {
						metaBoard->gameBoard->board[j][i].value *= 10;/*Insert another digit*/
						metaBoard->gameBoard->board[j][i].value += (*cell - '0');
					}
					cell++;/*Move to next character*/
				}
				cell -= size;/*Reset pointer back to the beginning*/
				checkCell(j, i, metaBoard->gameBoard->board[j][i].value, 1, metaBoard->gameBoard);
			}
		}
	}
	metaBoard->filledCells = filled;
	free(cell);
	fclose(ifp);
	printBoard(metaBoard);
}

void saveToFile(gameState *metaBoard, char *fileName) {
	FILE *ifp;
	int i, j;
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
