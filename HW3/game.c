#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser.h"
#include "MainAux.h"
#include "solver.h"

int countCells;
int **board;
int **sol;
int **tempBoard;
int rows, cols;

void copyBoard(int **srcBoard, int **trgtBoard) {
	int i, j;
	for (i = 0; i < rows * cols; i++) {
		for (j = 0; j < rows * cols; j++) {
			trgtBoard[i][j] = srcBoard[i][j];
		}
	}
}

int checkCell(int x, int y, int z) {
	int i, j;
	for (i = 0; i < cols * rows; i++) {/*Check row*/
		if (abs(board[i][y]) == z) {
			return 0;
		}
	}
	for (i = 0; i < cols * rows; i++) {/*Check column*/
		if (abs(board[x][i]) == z) {
			return 0;
		}
	}
	for (i = floor(x / rows) * rows; i < floor(x / rows) * rows + rows; i++) {
		for (j = floor(y / cols) * cols; i < floor(y / cols) * cols + cols;
				i++) {
			if (!(i == x) && (j == y)) {
				if (abs(board[i][j]) == z) {
					return 0;
				}
			}
		}
	}
	return 1;
}

void setBoard(int x, int y, int z) {
	if (board[x][y] >= 0) {
		if (z == 0){
			if (board[x][y] > 0){
				board[x][y] = 0;
				countCells--;
			}
		}
		else if (checkCell(x, y, z)) {
			board[x][y] = z;
			printBoard();
			countCells++;
			checkWin(countCells, cols, rows);
		} else {
			printf("Error: value is invalid\n");
		}
		printBoard(cols, rows, board);
	} else {
		printf("Error: cell is fixed\n");
	}
}

void hintBoard(int x, int y) {
	int solution;
	solution = abs(sol[x][y]);/*The appropriate number for this cell of the latest solution of the board is stored in this cell*/
	printf("Hint: set cell to %d\n", solution);
}

void validate() {
	copyBoard(board, tempBoard);
	if (solver(tempBoard, cols, rows, 0)) {
		copyBoard(tempBoard, sol);
		printf("Validation passed: board is solvable\n");
	} else {
		printf("Validation failed: board is unsolvable\n");
	}
}

void generateBoard(int hints) {
	int i, j;
	builder(cols, rows, sol, 0, 0);/*Sol will contain a completely solved board*/
	hinter(hints, cols, rows, sol);/*Adding fixed cells to the board*/
	copyBoard(sol, board);
	for (i = 0; i < rows * cols; i++) {
		for (j = 0; j < rows * cols; j++) {
			if (board[i][j] > 0)
				board[i][j] = 0;/*Erase unfixed cells in game board*/
		}
	}
}

void initalizeBoard() {
	int i;
	int hints = readBoard(&rows, &cols);/*Get number of hints and size of blocks from user (default 3*3 in this exercise)*/
	board = calloc(rows * cols, sizeof(int *));
	sol = calloc(rows * cols, sizeof(int *));
	tempBoard = calloc(rows * cols, sizeof(int *));
	for (i = 0; i < rows * cols; i++) {
		board[i] = calloc(rows * cols, sizeof(int));
		sol[i] = calloc(rows * cols, sizeof(int));
		tempBoard[i] = calloc(rows * cols, sizeof(int));
	}
	generateBoard(hints);
	printBoard(cols, rows, board);
}

void exitGame() {
	int i;
	for (i = 0; i < rows * cols; i++) {
		free(tempBoard[i]);
		free(sol[i]);
		free(board[i]);
	}
	free(tempBoard);
	free(sol);
	free(board);
}
