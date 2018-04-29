#include <stdio.h>
#include "MainAux.h"

#define cols 9
#define rows 9

int board[cols][rows][cols * rows + 1] = { 0 };
int countCells;

int checkCell(int x, int y, int z) {
	return x + y + z;
}

void setBoard(int x, int y, int z) {
	if (board[x][y][0] >= 0) {
		if (checkCell(x, y, z)) {
			board[x][y][0] = z;
			printBoard();
			countCells++;
			checkWin(countCells);
		} else {
			printf("Error: value is invalid\n");
		}
	} else {
		printf("Error: cell is fixed\n");
	}
}

void hintBoard(int x, int y) {
	int sol;
	if (board[x][y][0] < 0)
		sol = board[x][y][0]*-1;
	else
		sol = board[x][y][1];
	printf("Hint: set cell to %d\n", sol);
}
