
#ifndef GAME_H_
#define GAME_H_
#include "gameStructs.h"

void freeBoard(board *freeBird);
void initalizeBoard(board *newBoard);
/*The function allocates the memory needed for the board newBoard according to the values in it's rows and cols fields, as a 2-D array of type cell.
 *INPUT: board *newBoard - a pointer to a board that has values in it's rows and cols fields, and haven't had any memory allocated to it yet.*/
int checkCell(int x, int y, int z, board *check);
/*The function checks if the value z is a valid value in cell <x,y> of board check, which means it hasn't appeared in the row, column or block yet.
 *INPUT: int x,y - Integers representing the column and row of the cell to check by <x,y>.
 *		 int z - The value which we want to insert to the given cell.
 *		 board *check - a pointer to a valid board filled with values ranging from 0 to the board length.
 *OUTPUT: The function returns 0 if value z can't be inserted to the given cell, or 1 if it can be inserted.*/
int isErroneous(gameState *metaBoard);
void checkWin(gameState *metaBoard);
/*The function checks if the board is completely filled, and if so, prints an according message.
 *INPUT: gameState *metaBoard - a pointer to a gameState with field filledCells that represents the amount of cells already filled in the game board of the current game.*/
void setBoard(int x, int y, int z, gameState *metaBoard);
/*The function tries to set the value z in the cell <x,y> in the game board of the gameState metaBoard.
 *Value 0 erases the cell, fixed cells can't be changed, field filledCells of metaBoard updates accordingly, and the game board is printed after a successful move or an appropriate message if the move failed.
 *INPUT: int x,y - Integers representing the column and row of the cell the user wish to change by <x,y>.
 *		 int z - The value which we want to insert to the given cell, ranging from 0 (erase cell) to board length.
 *		 gameState *metaBoard - a pointer to a valid gameState with board gameBoard filled with numbers 0 to board length which we try to insert value z to in cell <x,y>.*/
int hintBoard(int x, int y, gameState *metaBoard);
/*The function returns a hint of a possible value to the given cell <x,y>, by using board sol as a valid solution to the board.
 *The hint may be not relevant, as sol is the last solution computed by the game initialization or the last validate command given.
 *INPUT: int x,y - Integers representing the column and row of the cell the user want hint by <x,y>.
 *		 board *sol - a pointer to a valid solution of the board, filled with integers ranging from 1 to board length.
 *OUTPUT: An integer between 1 and board length, equals to the value in cell <x,y> of the board sol.*/
void validate(gameState *metaBoard);
/*The function verifies the current gameBoard of gameState metaBoard is a valid board that can be completed by using brute-force algorithm to solve it, and prints an appropriate message accordingly.
 *INPUT: gameState *metaBoard - a pointer to a valid gameState with board gameBoard filled with numbers 0 to board length which we try to solve by brute-force.*/
void numOfSol(board *tmpBoard);
void undo(gameState *metaBoard);
void redo(gameState *metaBoard);
void generateBoard(gameState *metaBoard);
/*The function generates a valid board for the current game with the size and number of filled cells the user has given as input.
 *The function updates the boards solution and gameBoard of gameState metaBoard accordingly.
 *INPUT: gameState *metaBoard - a pointer to a valid gameState with boards solution and gameBoard with allocated memory, and without any values (all cells are 0).*/
void resetGame(gameState *metaBoard);
/*The function resets the game by freeing metaBoard boards solution and gameBoard memory and making them ready for a new allocation without wasting resources.
 *INPUT: gameState *metaBoard - a pointer to a gameState with allocated memory for boards solution and gameBoard that needs to be freed.*/
void exitGame(gameState *metaBoard);
/*The function exits the game by freeing all memory that still haven't been freed from gameState metaBoard, and terminates the program.
 *INPUT: gameState *metaBoard - a pointer to a gameState with allocated memory for boards solution and gameBoard and their cells that needs to be freed.*/

#endif /* GAME_H_ */
