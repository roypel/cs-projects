
#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "gameStructs.h"

void printBoard(board *playerBoard);
/*The function prints the input board with frame to each block, each cell that is filled is written with fixed cells marked with a dot before their value, and an empty cell is marked with three spaces.
 *INPUT: board *playerBoard - a pointer to a board filled with values ranging from 0 to board length, while 0 indicates an empty cell, and a fixed cell has it's field marked correctly.*/
void checkWin(gameState *metaBoard);
/*The function checks if the board is completely filled, and if so, prints an according message.
 *INPUT: gameState *metaBoard - a pointer to a gameState with field filledCells that represents the amount of cells already filled in the game board of the current game.*/
int getSeed(char *input);
/*The function handles the given seed from the command line and convert it from a string form to a valid integer.
 *INPUT: char *input - a string that holds a single integer without any other characters.
 *OUTPUT: The function returns the integer in the input string as an integer type.*/

#endif /* MAINAUX_H_ */
