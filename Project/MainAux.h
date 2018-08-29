#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "gameStructs.h"

void printBoard(gameState *metaBoard);
/*TODO: fix documentation for another parameter*/
/*The function prints the input board with frame to each block, each cell that is filled is written with fixed cells marked with a dot before their value, and an empty cell is marked with three spaces.
 *INPUT: board *playerBoard - a pointer to a board filled with values ranging from 0 to board length, while 0 indicates an empty cell, and a fixed cell has it's field marked correctly.*/
void printChanges(int from, int to);
void printForTest(board *gameBoard);
void checkInitalize(void *pointer, char *cmd);

#endif /* MAINAUX_H_ */
