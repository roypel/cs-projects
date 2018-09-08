#ifndef GAME_H_
#define GAME_H_
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
void setBoard(int x, int y, int z, gameState *metaBoard, int set);
/*The function tries to set the value z in the cell <x,y> in the game board of the gameState metaBoard.
 *Value 0 erases the cell, fixed cells can't be changed, field filledCells of metaBoard updates accordingly, and the game board is printed after a successful move or an appropriate message if the move failed.
 *The function updates erroneous cells, undo/redo list, and gameMode in case the user is in solve mode and filled the puzzle successfully.
 *INPUT: int x,y - Integers representing the column and row of the cell the user wish to change by <x,y>.
 *		 int z - The value which we want to insert to the given cell, ranging from 0 (erase cell) to board length.
 *		 gameState *metaBoard - A pointer to a valid gameState with board gameBoard filled with numbers 0 to board length which we try to insert value z to in cell <x,y>.
 *		 int set - A boolean parameter used in order to indicate if we want to advance the undo/redo list (1) or not (0) when not needed eg. while doing undo/redo*/
void hintBoard(int x, int y, gameState *metaBoard);
/*The function prints a hint of a possible value to the given cell <x,y>, by using ILP to find a board solution.
 *INPUT: int x,y - Integers representing the column and row of the cell the user want hint by <x,y>. Should not be fixed, or a hint won't be given and an appropriate message will be shown.
 *       gameState *metaBoard - A pointer to a gameState with allocated board with valid values, should not contain erroneous values or a hint won't be given and an appropriate message will be shown.*/
int validate(gameState *metaBoard);
/*The function verifies the current gameBoard of gameState metaBoard is a valid board that can be completed by using ILP to solve it, and return a value accordingly.
 *INPUT: gameState *metaBoard - A pointer to a valid gameState with board gameBoard filled with valid values which we try to solve by using ILP.
 *OUTPUT: The function returns (-1) if the ILP (Gurobi) has failed, (0) on an unsolvable board, and (1) if a solution was found and the board is valid.*/
void numOfSol(board *gameBoard);
/*The function finds all the possible solutions to the game board using an exhaustive backtracking algorithm, and prints an appropriate message.
 * INPUT: board *gameBoard - A pointer to an allocated board with valid values we try to fill in every possible way using exhaustive backtracking and find all possible solutions.*/
void generateBoard(int toFill, int toKeep, gameState *metaBoard);
/*The function generates a valid board for the current game by randomly filling toFill cells in the board, trying to solve it using ILP, and then keeping only toKeep values in it.
 * If there were 1000 failed generating attempts (couldn't find a legal value for a cell or no solution was found), the function prints an error message and empties the board.
 *INPUT: int toFill - The number of cells the function will try to randomly fill in the board.
 *       int toKeep - The number of filled cells the function will keep from the solved board.
 *       gameState *metaBoard - A pointer to a valid gameState with boards solution and gameBoard with allocated memory, and without any values (all cells are 0), or else the function won't generate a board.*/
void undo(gameState *metaBoard);
/*The function changes the board one move backward in the undo/redo linked list (if a move exists), reverting and printing any changes made in the last move, and moves the curentMove backwards.
 * INPUT: gameState *metaBoard - A pointer to a gameState with allocated undo/redo linked list and board with valid values in it.*/
void redo(gameState *metaBoard);
/*The function changes the board one move forward in the undo/redo linked list (if a move exists), reverting back and printing any changes made in the last undo, and moves the curentMove forward.
 * INPUT: gameState *metaBoard - A pointer to a gameState with allocated undo/redo linked list and board with valid values in it.*/
void resetGame(gameState *metaBoard);
/*The function resets the game board in metaBoard to be the original board the user loaded, by reverting all the changes made using undo, and then clearing the undo/redo list.
 *INPUT: gameState *metaBoard - A pointer to a gameState with allocated undo/redo linked list and board with valid values in it.*/
void exitGame(gameState *metaBoard);
/*The function exits the game by freeing all the memory that still haven't been freed from gameState metaBoard, and terminates the program.
 *INPUT: gameState *metaBoard - A pointer to a gameState with allocated memory for linked list, board and cells that needs to be freed.*/

#endif /* GAME_H_ */
