#ifndef SOLVER_H_
#define SOLVER_H_
#include "gameStructs.h"

int solver(board *tmpBoard, int index);
/*The function recursively tries to find a valid solution to tmpBoard by using brute-force method (trying all possible values in every empty cell from left to right, up to down).
 *The function starts to fill from place index (or next empty cell), and tries each possible value and send the board another step until it's filled or we ran out of options and need to backtrack without changing anything.
 *INPUT: board *tmpBoard - a pointer to a valid board filled with 0 in empty places and values between 1 to board length in fixed cells or user inputed cells.
 *		 int index - the cell we start the filling from, can be between 0 and board length squared.
 *OUTPUT: int representing if we failed to build a valid board (0) or succeed and found a valid solution (1)*/
void builder(board *buildBoard, int x, int y);
/*The function recursively builds a random board by trying any possible values (randomly chosen) for cell <x,y> in board buildBoard and moves on to finding value for the next cell recursively.
 * If no possible value is available we backtrack to the previous cell without changing the board to try a different value.
 * INPUT: board *buildBoard - a pointer to a valid board filled with 0 in empty places (from cell <x,y> onwards) and values between 1 to board length in all the cells up to cell <x,y>.
 * 		  x,y - integers between 0 to (board length - 1) representing the current cell we try to fill (x column, y row), if we pass the board size (try to access a row bigger than board length) we know we finished filling all the board.*/
void hinter(gameState *metaBoard);
/*The function randomly chooses cells (first column then row) which will be fixed for the current game, by the value the user entered on the beginning of the game.
 *The function updates the solution board of the gameState metaBoard with the correct cells to be fixed, while the rest of the cells remains unfixed, and no value is being changed on the board.
 *INPUT: gameState *metaBoard - a pointer to a gameState with a completely filled solution board and a field filledCells with the user input of the amount of cells they wish to be filled.*/

#endif /* SOLVER_H_ */
