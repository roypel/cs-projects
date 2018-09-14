/*Header file which contains the functions that tries to solve or add values to the board without the use of ILP*/

#ifndef SOLVER_H_
#define SOLVER_H_
#include "gameStructs.h"

int findNumSols(board *gameBoard);
/*The function tries to find all the valid solutions to the board by using brute-force method with exhaustive backtracking (trying all possible values in every empty cell from left to right, top to bottom).
 *The function starts to fill from the first empty cell, and tries each possible value and send the board another step until it's filled or we ran out of options and need to backtrack without changing anything.
 *The function keeps the information needed for backtracking using a stack.
 *INPUT: board *gameBoard - A pointer to an allocated gameBoard with valid values.
 *OUTPUT: int representing the amount of solutions the function found.*/
int fillSingleValues(gameState *metaBoard);
/*The function tries to find cells that only have a single value available to add to them, and if such a value exists,
 * sets the value of the cell to that value, prints an appropriate message and adds all the changes to the undo/redo list. May result in an erroneous board!
 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated game board with valid values that the function will try to fill "obvious" values to.
 * OUTPUT: int that represents the amount of cells that only had a single value available to them before we added that value to them*/
#endif /* SOLVER_H_ */
