#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

int nextEmptyCell(int index, int cols, int rows, int **board) {
	if (index == rows * rows * cols * cols) {/*We reached to the end of the board*/
		return -1;
	}
	if (board[index % (cols * rows)][(int) (floor(index / (rows * cols)))] == 0)/*Cell index is empty*/
		return index;
	return nextEmptyCell(index + 1, cols, rows, board);
}

int solver(int **board, int cols, int rows, int index) {
	int x, y, i;
	index = nextEmptyCell(index, cols, rows, board);/*Find next Empty Cell*/
	if (index == -1) {/*We reached the end of the board so we found a valid solution*/
		return 1;
	}
	x = index % (cols * rows);/*Extract the column of the cell by index*/
	y = (int) (floor(index / (rows * cols)));/*Extract the row of the cell by index*/
	for (i = 1; i < rows * cols + 1; i++) {
		if (checkCell(x, y, i)) {
			board[x][y] = i;
			if (solver(board, cols, rows, index + 1))/*Current board is a valid solution*/
				return 1;
			board[x][y] = 0;/*Current board isn't valid, need to increase input on cell*/
		}
	}
	return 0;/*Couldn't find a valid solution for cell*/
}

void builder(int cols, int rows, int **board, int x, int y) {
	int i, nextTry;
	int *posValues;
	if (y != rows * cols) {
		posValues = calloc(rows * cols + 1, sizeof(int));/*Possible values for cell <x,y>*/
		for (i = 1; i < rows * cols; i++) {
			if (checkCell(x, y, i)) {
				posValues[0]++;/*Amount of possible values for cell <x,y>*/
				posValues[posValues[0]] = i;
			}
		}
		while (posValues[0] != 0) {/*There are still possible values to insert to cell <x,y>*/
			if (posValues[0] == 1) {/*Only one possible value to insert, don't use random*/
				nextTry = 1;
			} else {
				nextTry = (rand() % posValues[0]) + 1;/*The index of the next random try*/
			}
			board[x][y] = posValues[nextTry];
			for (i = nextTry; i < posValues[0]; i++) {/*Shift left the possible values for continuity of the array*/
				posValues[i] = posValues[i + 1];
			}
			posValues[0]--;/*Update the remaining possible values*/
			if (x == rows * cols - 1)
				builder(cols, rows, board, 0, y + 1);/*Recursive call for next new row (Rightmost column,
				 we need to move to the leftmost column of the next row)*/
			else
				builder(cols, rows, board, x + 1, y);/*Recursive call for next right cell*/
			if (board[rows * cols - 1][rows * cols - 1] != 0)/*Board is full, no need for further tries*/
				break;
			board[x][y] = 0;
		}
		free(posValues);
	}
}

void hinter(int hints, int cols, int rows, int **board) {
	int x, y;
	while (hints) {/*As long as we need to add more hints*/
		x = rand() % (cols * rows);
		y = rand() % (cols * rows);
		if (board[x][y] > 0) {
			board[x][y] *= -1;
			hints--;
		}
	}
}

/*
 * int nextAttempt(int x, int y, int z, int cols, int rows, int **board) {
 if (z == rows * cols) {
 return 0;
 }
 if (checkCell(x, y, z)) {
 board[x][y] = z;
 return 1;
 }
 return nextAttempt(x, y, z + 1, cols, rows, board);
 }
 void nextEmptyCell(int *col,int *row){
 int i, j;
 for (i = 0; i < rows; i++) {
 for (j = 0; j < cols; j++) {
 if (board[j][i]==0)
 }
 int solver(int **board, int cols, int rows) {
 {
 while (board[j][i] < 10){
 checkCell(j,i, board[j][i]++);
 board[i][j] ++;

 }
 }
 }
 }
 return 1;
 }
 */
