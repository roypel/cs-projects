#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "gameStructs.h"
#include "linkedListFunc.h"
#include "stackFunc.h"
#include "MainAux.h"

int nextEmptyCell(int index, board *checkBoard) {
	/*The function recursively finds the next empty cell in board checkBoard, in case it exists (board not filled), starting search from input "index".
	 * The function assumes index is in the range of 0 to full board index.
	 *INPUT: int index - the cell we start the search from, can be between 0 and board length squared.
	 *		 board *checkBoard - a pointer to a valid board filled with 0 in empty places and values between 1 to board length in fixed cells or user inputed cells.
	 *OUTPUT: int representing index of the next empty cell counting from left to right, up to down numbering, or -1 if no such cell exists.*/
	int rows = checkBoard->rows;
	int cols = checkBoard->cols;
	if (index == rows * rows * cols * cols) {/*We reached to the end of the board*/
		return -1;
	}
	if (checkBoard->board[index % (cols * rows)][(int) (index / (rows * cols))].value
			== 0)/*Cell index is empty*/
		return index;
	return nextEmptyCell(index + 1, checkBoard);
}

int solver(board *gameBoard) {/*The function for the num_solutions command.We count how many solutions are for the current board and print
	accordingly.We each time try to find the next empty cell.If we don't find any,it means that we reached the end of the board and
	found a solution,so we increase the "solutions" counter.If we do,we try to fill it with a number.If it was filled,we add it to
	the stack as a cell that was filled with that number so that when we return to it later we know from what value to start trying
	to fill it next.If we didn't find a value to fill it with,then it means we can't fill the board in it's current state,so we have
	to go back a cell(that we filled) and try to fill it with other values,starting from the value of the cell that it is currently
	holding,which is stored in the stack as the cell index and the value that is currently in the cell,and we try to fill that cell with
	other values(bigger than the value stored since we inductionally tried smaller values already).We finish when we extract the first cell
	that was empty from the stack and we try to fill it with a value bigger than it can be filled with(if it's a 3x3 block board
	then when we try to fill it with the value 10),after which we return the value of the counter specified above.*/
	int x = 0, y = 0, i = 1, index = 0;
	int solutions = 0, rows = gameBoard->rows, cols = gameBoard->cols;
	int found = 1;
	item temp;
	stackPointer backStack;
	backStack.maxSize = cols * rows;
	backStack.stack = calloc(backStack.maxSize, sizeof(item));
	checkInitalize(backStack.stack, "calloc");
	backStack.size = 0;
	do {
		if (found) {/*We try to find a new cell to fill*/
			index = nextEmptyCell(index, gameBoard);/*Find next Empty Cell*/
			if (index == -1) {/*We reached the end of the board so we found a valid solution*/
				solutions++;
				temp = pop(&backStack);/*Pop the last cell that we have filled*/
				i = gameBoard->board[x][y].value + 1;/*Try bigger values for this cell*/
				x = temp.col;
				y = temp.row;
			} else {
				x = index % (cols * rows);/*Extract the column of the cell by index*/
				y = index / (rows * cols);/*Extract the row of the cell by index*/
				index++;
				i = 1;/*Try values from 1 since it's a new cell we try to fill*/
			}
		}
		/*If we didn't enter if, we backtracked so x, y and i were updated already for the last cell we entered to the stack*/
		found = 0;
		for (; i < rows * cols + 1; i++) {
			checkCell(x, y, i, 0, gameBoard);
			if (!gameBoard->board[x][y].error) {
				gameBoard->board[x][y].value = i;
				temp.col = x;
				temp.row = y;
				push(temp, &backStack);
				found = 1;
				temp = *(backStack.stack + backStack.size - 1);
				break;/*We found a fitting value to this cell, we move to next cell*/
			}
		}
		if (!found) {
			gameBoard->board[x][y].value = 0;/*We need to reverse the cell back to empty*/
			gameBoard->board[x][y].error = 0;
			if (backStack.size > 0) {
				temp = pop(&backStack);
				x = temp.col;/*We backtrack so we try bigger values for the last cell we entered*/
				y = temp.row;
				i = gameBoard->board[x][y].value + 1;/*Try bigger values for this cell*/
				index = temp.col + temp.row * rows * cols;
			}
		}
	} while ((backStack.size > 0) || (i < (cols * rows) + 1));
	gameBoard->board[x][y].value = 0;/*We reverse the first cell we entered back to empty*/
	gameBoard->board[x][y].error = 0;
	free(backStack.stack);
	return solutions;
}
int checkSingleValue(int x, int y, int z, gameState *metaBoard) {/*Checks if a value appears in a row/column/block of a cell*/
	int i, j;
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check row*/
		if (metaBoard->gameBoard->board[i][y].value == z) {
			return 0;
		}
	}
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {/*Check column*/
		if (metaBoard->gameBoard->board[x][i].value == z) {
			return 0;
		}
	}
	for (i = (x / metaBoard->cols) * metaBoard->cols;
			i < (int) (x / metaBoard->cols) * metaBoard->cols + metaBoard->cols;
			i++) {
		for (j = (y / metaBoard->rows) * metaBoard->rows;
				j
						< (int) (y / metaBoard->rows) * metaBoard->rows
								+ metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[i][j].value == z) {
				return 0;
			}
		}
	}
	return 1;
}

void autoFill(gameState *metaBoard) {/*Function that is called for the autofill command.Tries to find cells that only have a single value
	available to add to them that isn't erroneous,and if such a value exists,sets the value of the cell to that value,and adds
	the change to the undo/redomove array that appears in the undo/redo list*/
	int i, j, k, counter = 0, posValues;
	int *moves = (int *) malloc(0);
	checkInitalize(moves, "malloc");
	for (i = 0; i < metaBoard->cols * metaBoard->rows; i++) {
		for (j = 0; j < metaBoard->cols * metaBoard->rows; j++) {
			if (metaBoard->gameBoard->board[j][i].value != 0)
				continue;
			posValues = 0;
			for (k = 1; k <= metaBoard->rows * metaBoard->cols; k++) {/*Check the possible values to insert to the <i,j> cell*/
				if (checkSingleValue(j, i, k, metaBoard)) {
					if (posValues == 0)
						posValues = k;
					else {
						posValues = 0;
						break;
					}
				}
			}
			if (posValues == 0)/*Couldn't find a value to put in the cell or we had more than one value to put in the cell*/
				continue;
			else {/*This cell only had a single value that we could enter it,so we add it to the moves array!*/
				counter++;
				moves = realloc(moves, sizeof(int) * counter * 4);/*Reallocate extra space*/
				checkInitalize(moves, "realloc");
				moves[(counter - 1) * 4] = j;/*adds the change to the new move array*/
				moves[(counter - 1) * 4 + 1] = i;
				moves[(counter - 1) * 4 + 2] = 0;
				moves[(counter - 1) * 4 + 3] = posValues;
			}
		}
	}
	if (counter)/*Update the list only if any changes were made*/
		metaBoard->moves->currentMove = addNextMove(
				metaBoard->moves->currentMove, moves, counter);/*Update linked list of moves*/
	for (i = 0; i < counter; i++) {/*Enter values to board and check the cell for erroneous conflicts*/
		metaBoard->gameBoard->board[moves[i * 4]][moves[i * 4 + 1]].value =
				moves[i * 4 + 3];
		checkCell(moves[i * 4], moves[i * 4 + 1], moves[i * 4 + 3], 1,
				metaBoard->gameBoard);
	}
	metaBoard->filledCells += counter; /*Update amount of cells filled*/
	free(moves);
	printBoard(metaBoard);
	checkWin(metaBoard);
}
