#include <stdio.h>
#include <string.h>
#include <math.h>

void printBoard(int cols, int rows, int **board) {
	int i, j;
	for (i = 0; i < cols * rows; i++) {
		if (i % rows == 0) {
			for (j = 0; j < rows * cols * 3 + 2 * cols + 1; j++) {
				printf("-");
			}
			printf("\n");
		}
		for (j = 0; j < rows * cols; j++) {
			if (j == 0) {
				printf("|");
			}
			if (board[j][i] < 0)
				printf(" .%d", board[j][i] * (-1));
			else {
				printf("  ");
				if (board[j][i] == 0)
					printf(" ");
				else
					printf("%d", board[j][i]);
			}
			if (j % cols == cols - 1)
				printf(" |");
		}
		printf("\n");
	}
	for (j = 0; j < rows * cols * 3 + 2 * cols + 1; j++) {
		printf("-");
	}
	printf("\n");
}

int getSeed(char *input){
	int seed=0, i;
	for (i = 0; i < (int)strlen(input); i++) {
		seed += (input[i]-48)*pow(10,strlen(input)-i-1);
	}
	return seed;
}
/*	void printBoard(int cols, int rows, int ***board) {
 int i, j, charNum;
 for (i = 0; i < cols * rows + cols + 1; i++) {
 if (i % (rows + 1) == 0) {
 for (j = 0; j < rows * cols * 3 + 2 * cols + 1; j++) {
 printf("-");
 }
 } else {
 for (j = 0; j < rows * cols * 3 + 2 * cols + 1; j++) {
 charNum = j % (cols * 3 + 2);The index of the character in the block including left |
 if (charNum == 0) {
 printf("|");
 }
 if (charNum % 3 == 1){
 printf(" ");
 }
 else{if (board[j][i][0]<0)
 printf(".%d")

 }
 }

 }
 }
 printf("\n");
 }
 }*/

void checkWin(int countCells, int cols, int rows) {
	if (countCells == cols * cols * rows * rows) {
		printf("Puzzle solved successfully\n");

	}
}
