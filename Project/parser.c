#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "gameStructs.h"

#define inputSize 1024
#define setValues 3
#define hintValues 2
#define maxValues 3

int checkInput(int userCol, int userRow, int userVal, int col, int row,
		char *cmd) {
	/*Function checks if the input for set and hint has the correct amount of strings and is a valid input for current board
	 * userCol, userRow and userVal are the user inputs (if he entered any, else they valued at -2)
	 * col, row are current board size
	 * cmd is a string representing the command we need to check ,since hint and set have different requirements*/
	if (strcmp(cmd, "set") == 0) {
		if ((userCol == -2) || (userRow == -2) || (userVal == -1))/*We didn't read three strings after "set"*/
			printf("Error: invalid command\n");
		else {
			if (((userCol >= 0) && (userCol < col * row))/*Make sure input is valid for board*/
			&& ((userRow >= 0) && (userRow < col * row))
					&& ((userVal >= 0) && (userVal <= col * row)))
				return 1;
		}
	} else if (strcmp(cmd, "hint") == 0) {
		if ((userCol == -2) || (userRow == -2))/*We didn't read two strings after "hint"*/
			printf("Error: invalid command\n");
		else {
			if ((userCol >= 0) && (userCol < col * row) && (userRow >= 0)
					&& (userRow < col * row))/*Make sure input is valid for board*/
				return 1;
		}
	}
	return 0;
}

void readInput(gameState *metaBoard) {
	const char delim[5] = " \t\r\n";
	char input[inputSize] = { 0 };
	char *token;/*Separates input to tokens*/
	int values[maxValues], i, userCol, userRow, userVal, boardCol, boardRow;/*For the sake of readability we have excess variables*/
	initalizeGame(metaBoard);
	boardCol = metaBoard->cols;
	boardRow = metaBoard->rows;
	while (!feof(stdin)) {
		for (i = 0; i < maxValues; i++) {
			values[i] = -2;
		}
		fflush(stdin);
		if (fgets(input, inputSize, stdin) != NULL) {
			token = strtok(input, delim);
			if (token != NULL) {
				if ((strcmp(token, "set") == 0)
						&& (metaBoard->filledCells
								!= boardCol * boardCol * boardRow * boardRow)) {
					for (i = 0; i < setValues; i++) {/*Reading at least three strings after "set", else invalid input*/
						token = strtok(NULL, delim);
						if (token)
							values[i] = *token - 49;
					}
					userCol = values[0];
					userRow = values[1];
					userVal = values[2] + 1;/*Board set values should be between 0-9*/
					if (checkInput(userCol, userRow, userVal, boardCol,
							boardRow, "set"))
						setBoard(userCol, userRow, userVal, metaBoard);
				} else if ((strcmp(token, "hint") == 0)
						&& (metaBoard->filledCells
								!= boardCol * boardCol * boardRow * boardRow)) {
					for (i = 0; i < hintValues; i++) {/*Reading at least two strings after "hint", else invalid input*/
						token = strtok(NULL, delim);
						if (token)
							values[i] = *token - 49;
					}
					userCol = values[0];
					userRow = values[1];
					if (checkInput(userCol, userRow, userVal, boardCol,
							boardRow, "hint"))
						hintBoard(userCol, userRow, metaBoard->solution);
				} else if ((strcmp(token, "validate") == 0)
						&& (metaBoard->filledCells
								!= boardCol * boardCol * boardRow * boardRow)) {
					validate(metaBoard);
				} else if (strcmp(token, "restart") == 0) {
					resetGame(metaBoard);
					initalizeGame(metaBoard);
					boardCol = metaBoard->cols;
					boardRow = metaBoard->rows;
				} else if (strcmp(token, "exit") == 0) {
					exitGame(metaBoard);
				} else {
					printf("Error: invalid command\n");
				}
			}
		} else if (feof(stdin)) {
			exitGame(metaBoard);
		} else {
			printf("Error: fgets has failed\n");
			exit(0);
		}
	}
	exitGame(metaBoard);
}

void readBoard(gameState *metaBoard) {
	int hints, cols, rows, i;
	char input[inputSize] = { 0 };
	int fullBoard;
	int notValid = 1;/*A flag variable to record if the input was valid*/
	cols = 3;/*In this assignment the board size is already defined, in the future will be provided by user*/
	rows = 3;
	metaBoard->cols = cols;
	metaBoard->rows = rows;
	fullBoard = (metaBoard->rows * rows * cols * cols);
	while ((notValid) && (!feof(stdin))) {
printf("Please enter the number of cells to fill [0-%d]:\n", fullBoard - 1);/*The biggest number of fillings is whole board minus 1*/
		hints = 0;
		fflush(stdin);
		if (fgets(input, inputSize, stdin) != NULL) {
			if (input[0] != '\n') {/*If we read next line, we skip it*/
				for (i = 0; input[i] != '\n'; i++) {/*Read until next line*/
					if ((input[i] != (' ') && (input[i] != '\r') && (input[i] != '\t')) && (input[i] != EOF)) {/*Take into account only meaningful characters, also it's assumed that the input is a single integer*/
						hints = hints * 10 + (input[i] - 48);/*Translate the characters to int*/
					}
				}
				if ((hints >= fullBoard) || (hints < 0))/*Check if the amount of hints is valid*/
					printf(
							"Error: invalid number of cells to fill (should be between 0 and %d)\n",
							fullBoard - 1);
				else
					notValid = 0;/*Input is valid and we may continue*/
			}
		} else {
			printf("Error: fgets has failed\n");
			exit(0);
		}
	}
	if (feof(stdin)) {/*Received EOF before game initialized requires different procedure than exitGame function*/
		printf("Exiting...\n");
		free(metaBoard->solution);
		free(metaBoard->gameBoard);
		exit(0);
	}
	metaBoard->filledCells = hints;
}

