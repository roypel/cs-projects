#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "gameStructs.h"
#include "MainAux.h"
#include "fileFunc.h"
#include "solver.h"

#define inputSize 258 /*We want to check if the line consists 257 characters, and we need to save space for '\0'*/
#define setValues 3
#define hintValues 2
#define maxValues 3
#define generateValues 2
#define invalidError printf("ERROR: invalid command\n")
#define erroneousError printf("Error: board contains erroneous values\n")

int checkIsInt(char *input) {/*Get input string and check if all chars are digits, return the int or -1 if not positive integer*/
	unsigned int i;
	int num = 0;
	for (i = 0; i < strlen(input); i++) {
		if (!((input[i] >= '0') && (input[i] <= '9')))
			return -3;/*We received an input but it wasn't an int, values will hold -3 in this case (or less if we decrement outside)*/
		num *= 10;
		num += input[i] - '0';
	}
	return num;
}

int checkInput(int *values, gameState *metaBoard, char *cmd) {
	/*TODO: Fix documentation*/
	/*Function checks if the input for set and hint has the correct amount of strings and is a valid input for current board
	 * userCol, userRow and userVal are the user inputs (if he entered any, else they valued at -2)
	 * col, row are current board size
	 * cmd is a string representing the command we need to check ,since hint and set have different requirements*/
	int cols = metaBoard->cols, rows = metaBoard->rows, empty;
	if (!strcmp(cmd, "set")) {
		if ((values[0] == -2) || (values[1] == -2) || (values[2] == -1))/*We didn't read three strings after "set"*/
			invalidError;
		else {
			if (((values[0] >= 0) && (values[0] < cols * rows))/*Make sure input is valid for board*/
			&& ((values[1] >= 0) && (values[1] < cols * rows)) && ((values[2] >= 0) && (values[2] <= cols * rows)))
				return 1;
			else
				printf("Error: value not in range 0-%d\n", rows * cols);
		}
	} else if (!strcmp(cmd, "hint")) {
		if ((values[0] == -2) || (values[1] == -2))/*We didn't read two strings after "hint"*/
			invalidError;
		else {
			if ((values[0] >= 0) && (values[0] < cols * rows) && (values[1] >= 0) && (values[1] < cols * rows))/*Make sure input is valid for board*/
				return 1;
			else
				printf("Error: value not in range 1-%d\n", rows * cols);
		}
	} else if (!strcmp(cmd, "generate")) {
		if ((values[0] == -2) || (values[1] == -2))/*We didn't read two strings after "generate"*/
			invalidError;
		else {
			empty = cols * rows * cols * rows - metaBoard->filledCells;
			if ((values[0] >= 0) && (values[0] <= empty) && (values[1] >= 0) && (values[1] <= empty))/*Make sure input is valid for board*/
				return 1;
			else
				printf("Error: value not in range 0-%d\n", empty);
		}
	}
	return 0;
}

void ignoreLine(char *input) {
	invalidError;
	while (input[256] != 0) {
		input[256] = 0;
		checkInitalize(fgets(input, inputSize, stdin), "fgets");
	}
}

void cmdSolve(const char *delim, gameState *metaBoard) {
	char *token;
	token = strtok(NULL, delim);
	if (token) {
		sendToFill(metaBoard, token, Solve);
	} else
		invalidError;
}

void cmdEdit(const char *delim, gameState *metaBoard) {
	char *token;
	token = strtok(NULL, delim);
	sendToFill(metaBoard, token, Edit);
}

void cmdMarkErrors(const char *delim, int *values, gameState *metaBoard) {
	char *token;
	token = strtok(NULL, delim);
	if (token) {
		values[0] = checkIsInt(token);
		if ((values[0] == 0) || (values[0] == 1))
			metaBoard->markError = values[0];
		else
			printf("Error: the value should be 0 or 1\n");
	} else
		invalidError;
}

void cmdSet(const char *delim, int *values, gameState *metaBoard) {
	char *token;
	int i;
	for (i = 0; i < setValues; i++) {/*Reading at least three strings after "set", else invalid input*/
		token = strtok(NULL, delim);
		if (token)
			values[i] = checkIsInt(token) - 1;/*We decrement 1 so the values will fit array places that starts with 0*/
	}
	values[2]++;/*Fix value of what the user wants to enter to the cell, unneeded decrement*/
	if (checkInput(values, metaBoard, "set"))
		setBoard(values[0], values[1], values[2], metaBoard, 1);
}

void cmdValidate(gameState *metaBoard) {
	int valid;
	if (isErroneous(metaBoard))
		erroneousError;
	else {
		valid = validate(metaBoard);
		if (valid == 1)
			printf("Validation passed: board is solvable\n");
		else if (!valid)
			printf("Validation failed: board is unsolvable\n");
	}
}

void cmdGenerate(const char *delim, int *values, gameState *metaBoard) {
	char *token;
	int i;
	for (i = 0; i < generateValues; i++) {/*Reading at least two strings after "generate", else invalid input*/
		token = strtok(NULL, delim);
		if (token)
			values[i] = checkIsInt(token);
	}
	if (checkInput(values, metaBoard, "generate")) {
		if (metaBoard->filledCells != 0)
			printf("Error: board is not empty\n");
		else if (values[1] != 0)/*if Y=0 then the board stays empty and we don't need to add the command to the doubly linked list*/
			generateBoard(values[0], values[1], metaBoard);
	}
}

void cmdSave(const char *delim, gameState *metaBoard) {
	char *token;
	token = strtok(NULL, delim);
	if (token) {
		saveFile(metaBoard, token);
	} else
		invalidError;
}

void cmdHint(const char *delim, int *values, gameState *metaBoard) {
	char *token;
	int i;
	for (i = 0; i < hintValues; i++) {/*Reading at least two strings after "hint", else invalid input*/
		token = strtok(NULL, delim);
		if (token)
			values[i] = checkIsInt(token) - 1;/*We decrement 1 so the values will fit array places that starts with 0*/
	}
	if (checkInput(values, metaBoard, "hint")) {
		if (isErroneous(metaBoard))
			erroneousError;
		else
			hintBoard(values[0], values[1], metaBoard);
	}
}

void cmdNumSolutions(gameState *metaBoard) {
	if (isErroneous(metaBoard))
		erroneousError;
	else
		numOfSol(metaBoard->gameBoard);
}

void cmdAutofill(gameState *metaBoard) {
	if (isErroneous(metaBoard))
		erroneousError;
	else {
		autoFill(metaBoard);
	}
}

void readInput(gameState *metaBoard) {
	const char delim[5] = " \t\r\n";
	char input[inputSize] = { 0 };
	char *token;/*Separates input to tokens*/
	int values[maxValues], i;/*For the sake of readability we have excess variables*/
	while (!feof(stdin)) {
		for (i = 0; i < maxValues; i++) {/*Resets values array to know if new input is valid (for relevant functions)*/
			values[i] = -2;/*If a cell in values contains -2, we know the user didn't enter a value to this cell (we convert the input string to a positive int)*/
		}
		fflush(stdin);
		printf("Enter your command:\n");
		if (fgets(input, inputSize, stdin) != NULL) {
			if (input[256] != 0) {/*Skip current line, too much characters in input*/
				ignoreLine(input);
			} else {
				token = strtok(input, delim);
				if (token != NULL) {
					if (!strcmp(token, "solve")) {
						cmdSolve(delim, metaBoard);
					} else if (!strcmp(token, "edit")) {
						cmdEdit(delim, metaBoard);
					} else if (!(strcmp(token, "mark_errors")) && (metaBoard->mode == Solve)) {
						cmdMarkErrors(delim, values, metaBoard);
					} else if (!(strcmp(token, "print_board")) && (metaBoard->mode != Init)) {
						printBoard(metaBoard);
					} else if ((!(strcmp(token, "set"))) && (metaBoard->mode != Init)) {
						cmdSet(delim, values, metaBoard);
					} else if (!(strcmp(token, "validate")) && (metaBoard->mode != Init)) {
						cmdValidate(metaBoard);
					} else if (!strcmp(token, "generate") && (metaBoard->mode == Edit)) {
						cmdGenerate(delim, values, metaBoard);
					} else if (!strcmp(token, "undo") && (metaBoard->mode != Init)) {
						undo(metaBoard);
					} else if (!strcmp(token, "redo") && (metaBoard->mode != Init)) {
						redo(metaBoard);
					} else if (!strcmp(token, "save") && (metaBoard->mode != Init)) {
						cmdSave(delim, metaBoard);
					} else if ((strcmp(token, "hint") == 0) && (metaBoard->mode == Solve)) {
						cmdHint(delim, values, metaBoard);
					} else if (!strcmp(token, "num_solutions") && (metaBoard->mode != Init)) {
						cmdNumSolutions(metaBoard);
					} else if (!strcmp(token, "autofill") && (metaBoard->mode == Solve)) {
						cmdAutofill(metaBoard);
					} else if (!strcmp(token, "reset") && (metaBoard->mode != Init)) {
						resetGame(metaBoard);
					} else if (!strcmp(token, "exit")) {
						exitGame(metaBoard);
					} else {
						invalidError;
					}
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
