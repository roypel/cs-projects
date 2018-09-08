#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "gameStructs.h"

void printBoard(gameState *metaBoard);
/*The function prints the input board with frame for each block, each cell that is filled is written,
 * with fixed cells marked with a dot before their value, erroneous cells marked with an asterisk and an empty cell is marked with four spaces.
 *INPUT: gameState *metaBoard - A pointer to a gameState with allocated board and valid values in it, and erroneous and fixed properties of each cell are correctly maintained.*/
void printChanges(int from, int to);
/*The function prints the changes made in the board by changing a cell from the value from to the value to.
 * INPUT: int from - The previous value that was in the cell.
 *        int to - the new value that is currently in the cell.*/
void checkInitalize(void *pointer, char *cmd);
/*The function checks if the pointer was initialized correctly (not NULL) and if it isn't initialized correctly, prints an error message and exits the program.
 * INPUT: void *pointer - A pointer the function will check if it was initialized properly.
 *        char *cmd - The command that was issued (calloc, malloc...) that may have failed, used to generate a correct error message.*/

#endif /* MAINAUX_H_ */
