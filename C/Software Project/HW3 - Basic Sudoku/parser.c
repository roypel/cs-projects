#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "gameStructs.h"

#define inputSize 1024

int checkInput(char *token) {
	while (token != NULL) {

	}
	return 1;
}

void readInput(gameState *metaBoard) {
	const char delim[5] = " \t\r\n";
	char input[inputSize] = { 0 };
	char *token;/*Separates input to tokens*/
	int x, y, z;
	initalizeGame(metaBoard);
	while (!feof(stdin)) {
		fflush(stdin);
		if (fgets(input, inputSize, stdin) != NULL) {
			token = strtok(input, delim);
			if (token != NULL) {
				if (strcmp(token, "set") == 0) {
					x = *strtok(NULL, delim) - 49;
					y = *strtok(NULL, delim) - 49;
					z = *strtok(NULL, delim) - 48;
					if ((x >= 0) && (x < metaBoard->cols * metaBoard->rows))
						if ((y >= 0) && (y < metaBoard->cols * metaBoard->rows))
							if ((z >= 0)
									&& (z <= metaBoard->cols * metaBoard->rows))
								setBoard(x, y, z, metaBoard);
				} else if (strcmp(token, "hint") == 0) {
					x = *strtok(NULL, delim) - 49;
					y = *strtok(NULL, delim) - 49;
					if ((x >= 0) && (x < metaBoard->cols * metaBoard->rows))
						if ((y >= 0) && (y < metaBoard->cols * metaBoard->rows))
							hintBoard(x, y, metaBoard->solution);
				} else if (strcmp(token, "validate") == 0) {
					validate(metaBoard);
				} else if (strcmp(token, "restart") == 0) {
					exitGame(metaBoard);
					initalizeGame(metaBoard);
				} else if (strcmp(token, "exit") == 0) {
					printf("Exiting...\n");
					exitGame(metaBoard);
					free(metaBoard->solution);
					free(metaBoard->gameBoard);
					exit(0);
				} else {
					printf("Error: invalid command\n");
				}
			}
		} else {
			printf("Error: fgets has failed\n");
			exit(0);
		}
	}
	printf("Exiting...\n");
	exitGame(metaBoard);
	free(metaBoard->solution);
	free(metaBoard->gameBoard);
	exit(0);
}
void readBoard(gameState *metaBoard) {
	int hints, cols, rows, i;
	char input[inputSize] = { 0 };
	int fullBoard;
	int notValid = 1;/*A flag variable to record if the input was valid*/
	cols = 3;/*In this assignment the board size is already defined*/
	rows = 3;
	metaBoard->cols = cols;
	metaBoard->rows = rows;
	fullBoard = (metaBoard->rows * rows * cols * cols);
	printf("Please enter the number of cells to fill [0-%d]:\n", fullBoard - 1);/*The biggest number of fillings is whole board minus 1*/
	while ((notValid) && (!feof(stdin))) {
		hints = 0;
		if (fgets(input, inputSize, stdin) != NULL) {
			if (input[0] != '\n') {
				for (i = 0; input[i] != '\n'; i++) {
					if ((input[i] != (' ')) && (input[i] != EOF)) {
						hints = hints * 10 + (input[i] - 48);
					}
				}
				if ((hints >= fullBoard) || (hints < 0))/*Check if the amount of hints is valid*/
					printf(
							"Error: Invalid number of cells to fill (should be between 0 and %d)\n",
							fullBoard - 1);
				else
					notValid = 0;
			}
		} else {
			printf("Error: fgets has failed\n");
			exit(0);
		}
	}
	if (feof(stdin)) {
		printf("Exiting...\n");
		free(metaBoard->solution);
		free(metaBoard->gameBoard);
		exit(0);
	}
	metaBoard->filledCells = hints;
}

