#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "MainAux.h"
#include "solver.h"
#include "gameStructs.h"

void freeBoard(board *freeBird){
	int i;
	for(i = 0; i < freeBird->rows * freeBird->cols; i++){
			free(freeBird->board[i]);
		}
		free(freeBird->board);
		free(freeBird);
}

void initalizeBoard(board *newBoard) {
	int i;
	newBoard->board = calloc(newBoard->rows * newBoard->cols, sizeof(cell *));
	for (i = 0; i < newBoard->rows * newBoard->cols; i++) {
		newBoard->board[i] = calloc(newBoard->rows * newBoard->cols, sizeof(cell));
	}
}

void copyBoard(board *srcBoard, board *trgtBoard){
	int i, j;
	for (i = 0; i < srcBoard->cols * srcBoard->rows; i++) {
		for (j = 0; j < srcBoard->rows * srcBoard->cols; j++) {
			trgtBoard->board[i][j]->value = srcBoard->board[i][j]->value;
		}
	}
}

int checkCell(int x, int y, int z, board *check) {
	int i, j;
	for (i = 0; i < check->cols * check->rows; i++) {/*Check column*/
		if (check->board[i][y]->value == z) {
			return 0;
		}
	}
	for (i = 0; i < check->cols * check->rows; i++) {/*Check row*/
		if (check->board[x][i]->value == z) {
			return 0;
		}
	}
	for (i = (x / check->rows) * check->rows; i < (int)(x / check->rows) * check->rows + check->rows; i++) {
		for (j = (y / check->cols) * check->cols; j < (int)(y / check->cols) * check->cols + check->cols;	j++) {
			if (!((i == x) && (j == y))) {
				if (check->board[i][j]->value == z) {
					return 0;
				}
			}
		}
	}
	return 1;
}

void setBoard(int x, int y, int z, gameState *metaBoard) {
	if (!metaBoard->gameBoard->board[x][y]->fixed) {
		if (z == 0){/*User tries to erase a value on the board*/
			if (metaBoard->gameBoard->board[x][y]->value > 0){/*Check if we erase a value on the board or cell is already empty*/
				metaBoard->gameBoard->board[x][y]->value = 0;
				metaBoard->filledCells--;
			}
		}
		else if (checkCell(x, y, z, metaBoard->gameBoard)) {
			metaBoard->gameBoard->board[x][y]->value = z;
			printBoard(metaBoard->gameBoard);
			metaBoard->filledCells++;
			checkWin(metaBoard);
		} else {
			printf("Error: value is invalid\n");
		}
		printBoard(metaBoard->gameBoard);
	} else {
		printf("Error: cell is fixed\n");
	}
}

void hintBoard(int x, int y, board *sol) {
	int solution;
	solution = sol->board[x][y]->value;/*The appropriate number for this cell of the latest solution of the board is stored in this cell*/
	printf("Hint: set cell to %d\n", solution);
}

void validate(gameState *metaBoard) {
	int rows = metaBoard->gameBoard->rows;
	int cols = metaBoard->gameBoard->cols;
	board tempBoard;
	tempBoard->rows = rows;
	tempBoard->cols = cols;
	initalizeBoard(tempBoard);
	copyBoard(metaBoard->gameBoard, tempBoard);
	if (solver(tempBoard, 0)) {
		copyBoard(tempBoard, metaBoard->solution);
		printf("Validation passed: board is solvable\n");
	} else {
		printf("Validation failed: board is unsolvable\n");
	}
	freeBoard(tempBoard);
}

void generateBoard(gameState *metaBoard) {
	int i, j;
	builder(metaBoard->solution, 0, 0);/*metaBoard->solution will contain a completely solved board*/
	hinter(metaBoard);/*Adding fixed cells to the board*/
	copyBoard(metaBoard->solution, metaBoard->gameBoard);
	for (i = 0; i < metaBoard->rows * metaBoard->cols; i++) {
		for (j = 0; j < metaBoard->rows * metaBoard->cols; j++) {
			if (!metaBoard->gameBoard->board[i][j]->fixed)
				metaBoard->gameBoard->board[i][j]->value = 0;/*Erase unfixed cells in game board*/
		}
	}
}

void initalizeGame(gameState *metaBoard){
	readBoard(metaBoard);/*Get number of hints and size of blocks from user (default 3*3 in this exercise)*/
	metaBoard->solution->rows = metaBoard->rows;
	metaBoard->solution->cols = metaBoard->cols;
	metaBoard->gameBoard->rows = metaBoard->rows;
	metaBoard->gameBoard->cols = metaBoard->cols;
	initalizeBoard(metaBoard->solution);
	initalizeBoard(metaBoard->gameBoard);
	generateBoard(metaBoard);
	printBoard(metaBoard->gameBoard);
}

void exitGame(gameState *metaBoard) {
	freeBoard(metaBoard->solution);
	freeBoard(metaBoard->gameBoard);
	free(metaBoard);

}
