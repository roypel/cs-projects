#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "gameStructs.h"

void freeBoard(board *freeBird);
/*The function frees the memory allocated for the board in the input, starting from each row and then frees the board itself.
 *INPUT: board *freeBird - A pointer to an allocated board which can be freed to reduce the needed resources of the program.*/
void initalizeBoard(board *newBoard);
/*The function allocates the memory needed for the board newBoard according to the values in it's rows and cols fields, as a 2-D array of type cell.
 *INPUT: board *newBoard - A pointer to a board that has values in it's rows and cols fields, and haven't had any memory allocated to it yet.*/
void checkCell(int x, int y, int z, int change, board *check);
/*The function checks if the value z is a valid value in cell <x,y> of board check, which means it hasn't appeared in the row, column or block yet.
 *INPUT: int x,y - Integers representing the column and row of the cell to check by <x,y>.
 *		 int z - The value which we want to insert to the given cell.
 *		 int change - Indicates if we wish to enter the value to the cell (1), therefore changing the error property of the corresponding cells, or we just check if it's a valid value and won't enter it (0).
 *		 board *check - A pointer to a valid board filled with values ranging from 0 to the board length.
 *OUTPUT: The function returns 0 if value z can't be inserted to the given cell, or 1 if it can be inserted.*/
int isErroneous(gameState *metaBoard);
/*The function checks if there is any cell that contains an erroneous value by checking each cell error property.
 * INPUT: gameState *metaBoard - A pointer to a gameState with allocated board and valid values in it, where each erroneous cell is marked by the error property of the cell.
 * OUTPUT: The function returns 1 if there was an erroneous cell in the board, or 0 if none was found.*/
void checkWin(gameState *metaBoard);
/*The function checks if the board is completely filled correctly, and prints an according message and change the gameMode to Init if needed.
 *INPUT: gameState *metaBoard - A pointer to a gameState with field filledCells that represents the amount of cells already filled in the game board of the current game.*/
void checkInitalize(void *pointer, char *cmd);
/*The function checks if the pointer was initialized correctly (not NULL) and if it isn't initialized correctly, prints an error message and exits the program.
 * INPUT: void *pointer - A pointer the function will check if it was initialized properly.
 *        char *cmd - The command that was issued (calloc, malloc...) that may have failed, used to generate a correct error message.*/

#endif /* MAINAUX_H_ */
