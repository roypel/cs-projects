#ifndef SOLVER_H_
#define SOLVER_H_
#include "gameStructs.h"

int solver(board *gameBoard);
/*TODO: fix documentation*/
/*The function recursively tries to find a valid solution to tmpBoard by using brute-force method (trying all possible values in every empty cell from left to right, up to down).
 *The function starts to fill from place index (or next empty cell), and tries each possible value and send the board another step until it's filled or we ran out of options and need to backtrack without changing anything.
 *INPUT: board *tmpBoard - a pointer to a valid board filled with 0 in empty places and values between 1 to board length in fixed cells or user inputed cells.
 *		 int index - the cell we start the filling from, can be between 0 and board length squared.
 *OUTPUT: int representing if we failed to build a valid board (0) or succeed and found a valid solution (1)*/
void autoFill(gameState *metaBoard);
/*Function that is called for the autofill command.Tries to find cells that only has a single value
	available to add to them,and if such a value exists,sets the value of the cell to that value,and adds the change to the undo/redo
	move array that appears in the undo/redo list*/

#endif /* SOLVER_H_ */
