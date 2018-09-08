#ifndef SOLVER_H_
#define SOLVER_H_
#include "gameStructs.h"

int solver(board *gameBoard);
/*The function recursively tries to find a valid solution to the board by using brute-force method (trying all possible values in every empty cell from left to right, up to down).
 *The function starts to fill from the first empty cell, and tries each possible value and send the board another step until it's filled or we ran out of options and need to backtrack without changing anything.
 *INPUT: board *gameBoard - a pointer to the game board
 *OUTPUT: int representing if we failed to build a valid board (0) or succeed and found a valid solution (1)*/
void autoFill(gameState *metaBoard);
/*Function that is called for the autofill command.Tries to find cells that only has a single value
available to add to them,and if such a value exists,sets the value of the cell to that value,and adds the change to the undo/redo
move array that appears in the undo/redo list
INPUT-gameState *metaBoard the struct that contains the board that we want to autofill*/
#endif /* SOLVER_H_ */
