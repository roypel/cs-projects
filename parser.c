#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "gameStructs.h"
#include "mainAux.h"

#define inputSize 258 /*We want to check if the line consists 257 characters, and we need to save space for '\0'*/
#define setValues 3
#define hintValues 2
#define maxValues 3
#define generateValues 2
#define invalidError printf("ERROR: invalid command\n")
#define erroneousError printf("Error: board contains erroneous values\n")
#define delimiter " \t\r\n"

int checkIsInt(char *input) {
	/*The function checks if all the characters in the input string are digits, and if so returns the number they represent.
	 * INPUT: char *input - The input the user has entered. We don't assume anything about it.
	 * OUTPUT: An integer representing the number the user entered as input if it was a valid int, or (-3) if it's not a valid integer.*/
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
	/*The function checks if the input for the command cmd has the correct amount of strings and is a valid input for current board.
	 * INPUT: int *values - Array that holds the first user inputs (if he entered any, or else their value is -2) in the order he entered it.
	 *        gameState *metaBoard - A valid gameState pointer with preallocated board gameBoard with valid values.
	 *        char *cmd  - A string representing the command we need to check, since set, hint and generate have different requirements.
	 * OUTPUT: The function returns 1 if the values are valid for the command, or 0 if they are not valid, and an error message is printed accordingly.*/
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
	/*The function is used to skip a line of input if it has more than 256 characters, and print an error message.
	 * INPUT: char *input - The input the user has entered, supposed to have more than 256 characters.*/
	invalidError;
	while (input[256] != 0) {
		input[256] = 0;
		checkInitalize(fgets(input, inputSize, stdin), "fgets");
	}
}

void cmdSolve(gameState *metaBoard) {
	/*The function is an envelope function for the command "solve", it is issued if the user entered "solve" as a command, and checks the requirements to issue the command.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	char *token;
	token = strtok(NULL, delimiter);
	if (token) {
		startPuzzle(metaBoard, token, Solve);
	} else
		invalidError;
}

void cmdEdit(gameState *metaBoard) {
	/*The function is an envelope function for the command "edit", it is issued if the user entered "edit" as a command, and checks the requirements to issue the command.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	char *token;
	token = strtok(NULL, delimiter);
	startPuzzle(metaBoard, token, Edit);
}

void cmdMarkErrors(int *values, gameState *metaBoard) {
	/*The function is an envelope function for the command "mark_errors", it is issued if the user entered "mark_errors" as a command, and checks the requirements to issue the command.
	 * INPUT: int *values - An array that will hold the additional values the user will input that will be checked for the command.
	 *        gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	char *token;
	token = strtok(NULL, delimiter);
	if (token) {
		values[0] = checkIsInt(token);
		if ((values[0] == 0) || (values[0] == 1))/*Check if the value is 0 or 1*/
			metaBoard->markError = values[0];
		else
			printf("Error: the value should be 0 or 1\n");
	} else
		invalidError;
}

void cmdSet(int *values, gameState *metaBoard) {
	/*The function is an envelope function for the command "set", it is issued if the user entered "set" as a command, and checks the requirements to issue the command.
	 * INPUT: int *values - An array that will hold the additional values the user will input that will be checked for the command.
	 *        gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	char *token;
	int i;
	for (i = 0; i < setValues; i++) {/*Reading at least three strings after "set", else invalid input*/
		token = strtok(NULL, delimiter);
		if (token)
			values[i] = checkIsInt(token) - 1;/*We decrement 1 so the values will fit array places that starts with 0.*/
	}
	values[2]++;/*Fix the value of what the user wants to enter to the cell, it had unneeded decrement*/
	if (checkInput(values, metaBoard, "set"))
		setBoard(values[0], values[1], values[2], metaBoard, 1);
}

void cmdValidate(gameState *metaBoard) {
	/*The function is an envelope function for the command "validate", it is issued if the user entered "validate" as a command, and checks the requirements to issue the command.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	int valid;
	if (isErroneous(metaBoard))
		erroneousError;
	else {
		valid = validate(metaBoard);
		if (valid == 1)/*Return value is 1==valid*/
			printf("Validation passed: board is solvable\n");
		else if (!valid)/*Return value is 0==invalid*/
			printf("Validation failed: board is unsolvable\n");
	}/*Return value is not 0 or 1 == it is -1==something went wrong inside validate and printed accordingly in there*/
}

void cmdGenerate(int *values, gameState *metaBoard) {
	/*The function is an envelope function for the command "generate", it is issued if the user entered "generate" as a command, and checks the requirements to issue the command.
	 * INPUT: int *values - An array that will hold the additional values the user will input that will be checked for the command.
	 *        gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	char *token;
	int i;
	for (i = 0; i < generateValues; i++) {/*Reading at least two strings after "generate", else invalid input*/
		token = strtok(NULL, delimiter);
		if (token)
			values[i] = checkIsInt(token);
	}
	if (checkInput(values, metaBoard, "generate")) {
		if (metaBoard->filledCells != 0)
			printf("Error: board is not empty\n");
		else if (values[1] != 0)/*If Y=0 then the board stays empty and we don't need to add the command to the doubly linked list*/
			generateBoard(values[0], values[1], metaBoard);
		else
			printBoard(metaBoard);/*We still want to print the board if Y is equal to 0*/
	}
}

void cmdSave(gameState *metaBoard) {
	/*The function is an envelope function for the command "save", it is issued if the user entered "save" as a command, and checks the requirements to issue the command.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	char *token;
	token = strtok(NULL, delimiter);
	if (token) {
		saveBoard(metaBoard, token);
	} else
		invalidError;
}

void cmdHint(int *values, gameState *metaBoard) {
	/*The function is an envelope function for the command "hint", it is issued if the user entered "hint" as a command, and checks the requirements to issue the command.
	 * INPUT: int *values - An array that will hold the additional values the user will input that will be checked for the command.
	 *        gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	char *token;
	int i;
	for (i = 0; i < hintValues; i++) {/*Reading at least two strings after "hint", else invalid input*/
		token = strtok(NULL, delimiter);
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
	/*The function is an envelope function for the command "num_solutions", it is issued if the user entered "num_solutions" as a command, and checks the requirements to issue the command.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	if (isErroneous(metaBoard))
		erroneousError;
	else
		numOfSol(metaBoard->gameBoard);
}

void cmdAutofill(gameState *metaBoard) {
	/*The function is an envelope function for the command "autofill", it is issued if the user entered "autofill" as a command, and checks the requirements to issue the command.
	 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated board and valid values in it.*/
	if (isErroneous(metaBoard))
		erroneousError;
	else {
		autofill(metaBoard);
	}
}

void readInput(gameState *metaBoard) {
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
				token = strtok(input, delimiter);
				if (token != NULL) {
					if (!strcmp(token, "solve")) {
						cmdSolve(metaBoard);
					} else if (!strcmp(token, "edit")) {
						cmdEdit(metaBoard);
					} else if (!(strcmp(token, "mark_errors")) && (metaBoard->mode == Solve)) {
						cmdMarkErrors(values, metaBoard);
					} else if (!(strcmp(token, "print_board")) && (metaBoard->mode != Init)) {
						printBoard(metaBoard);
					} else if ((!(strcmp(token, "set"))) && (metaBoard->mode != Init)) {
						cmdSet(values, metaBoard);
					} else if (!(strcmp(token, "validate")) && (metaBoard->mode != Init)) {
						cmdValidate(metaBoard);
					} else if (!strcmp(token, "generate") && (metaBoard->mode == Edit)) {
						cmdGenerate(values, metaBoard);
					} else if (!strcmp(token, "undo") && (metaBoard->mode != Init)) {
						undo(metaBoard);
					} else if (!strcmp(token, "redo") && (metaBoard->mode != Init)) {
						redo(metaBoard);
					} else if (!strcmp(token, "save") && (metaBoard->mode != Init)) {
						cmdSave(metaBoard);
					} else if ((strcmp(token, "hint") == 0) && (metaBoard->mode == Solve)) {
						cmdHint(values, metaBoard);
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
