#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "SPBufferset.h"
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
	char *token;
	int x, y, z;
	while (1) {
		fgets(input, inputSize, stdin);
		token = strtok(input, delim);
	if (strcmp(token, "set") == 0) {
		x = *strtok(NULL, delim);
		y = *strtok(NULL, delim);
		z = *strtok(NULL, delim);
		setBoard(x,y,z);
	} else if (strcmp(token, "hint") == 0) {
		x = *strtok(NULL, delim);
		y = *strtok(NULL, delim);
		hintBoard(x,y);
	}
	else if (strcmp(token, "validate") == 0) {
	}
	else if (strcmp(token, "restart") == 0) {
	}
	else if (strcmp(token, "exit") == 0) {
	}
	else{
		printf("Error: invalid command\n");
	}
}
}
