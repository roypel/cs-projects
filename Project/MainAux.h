#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "gameStructs.h"

void printBoard(gameState *metaBoard);
/*The function prints the input board with frame to each block, each cell that is filled is written with fixed cells marked with a dot before their value, and an empty cell is marked with three spaces.
 *INPUT: board *playerBoard - a pointer to a board filled with values ranging from 0 to board length, while 0 indicates an empty cell, and a fixed cell has it's field marked correctly.*/
void printChanges(int from, int to);
/*Prints the changes that happened to the board when we used either the undo or the redo command.From is the number that was in the cell
 before the command,and to is the number that will be in the cell after the command*/
void checkInitalize(void *pointer, char *cmd);/*A modular command which we use in order to check if initialization of pointers such as in
commands like malloc has been successfully done or not,and if not then print a message and exit accordingly*/

#endif /* MAINAUX_H_ */
