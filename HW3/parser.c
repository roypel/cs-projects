#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

#define inputSize 1024

int checkInput(char *token) {
	while (token != NULL) {

	}
	return 1;
}

void readInput() {
	const char delim[5] = " \t\r\n";
	char input[inputSize] = { 0 };
	char *token;/*Separates input to tokens*/
	int x, y, z;
	initalizeBoard();
	while (1) {
		fgets(input, inputSize, stdin);
		token = strtok(input, delim);
		if (strcmp(token, "set") == 0) {
			printf("ok1");
			x = *strtok(NULL, delim);
			y = *strtok(NULL, delim);
			z = *strtok(NULL, delim);
			setBoard(x - 1, y - 1, z);
		} else if (strcmp(token, "hint") == 0) {
			printf("ok2");
			x = *strtok(NULL, delim) - 1;
			y = *strtok(NULL, delim) - 1;
			hintBoard(x, y);
		} else if (strcmp(token, "validate") == 0) {
			printf("ok3");
			validate();
		} else if (strcmp(token, "restart") == 0) {
			printf("ok4");
			exitGame();
			initalizeBoard();
		} else if (strcmp(token, "exit") == 0) {
			printf("ok5");
			printf("Exiting…\n");
			exitGame();
			exit(0);
		} else {
			printf("ok6");
			printf("Error: invalid command\n");
		}
		printf("ok7");
	}
	printf("ok8");
}
int readBoard(int *rows, int *cols) {
	int hints;
	int fullBoard;
	int notValid = 1;/*A flag variable to record if the input was valid*/
	*rows = 3;/*In this assignment the board size is already defined*/
	*cols = 3;
	fullBoard = ((*rows) * (*rows) * (*cols) * (*cols));
	printf("Please enter the number of cells to fill [0-%d]:\n", fullBoard - 1);/*The biggest number of fillings is whole board minus 1*/
	while (notValid) {
		hints = 0;
		scanf("%d ", &hints);
		if ((hints >= fullBoard) || (hints < 0))/*Check if the amount of hints is valid*/
			printf(
					"Error: Invalid number of cells to fill (should be between 0 and %d)\n",
					fullBoard - 1);
		else
			notValid = 0;
	}
	return hints;
}

