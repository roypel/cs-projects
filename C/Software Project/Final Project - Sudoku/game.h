/* Header file which contains the functions that we use in order to execute the different commands of the game. Including the functions:
 * startPuzzle - The function needs an allocated gameState, a file name (optional in edit mode) of a valid sudoku board, and a valid gameMode.
 *               The function will try to load the file to the board in gameState and update the relevant fields, and if it successfully did so,
 *               update the gameState gameMode to the provided gameMode. In edit mode without a file name, an empty 3*3 sudoku board will be loaded by default.
 * setBoard - The function needs a column and a row of a cell, and a value that if possible will be in the cell after the function finishes, a valid gameState
 *            with correctly maintained fields for each cell, and a parameter set (0 or 1) which will indicate if the undo/redo list should be updated as well.
 *            The function will try to enter the value to the specified cell, update the game board cells and undo/redo list if needed.
 * validate - The function needs a valid gameState with a board already loaded into it.
 *            The function will check if the board has a valid solution or not, and will return 1 if it has a solution or 0 if it doesn't.
 * generateBoard - The function needs two parameters, the first indicate how many cells we will try to fill into the board, and the second will indicate
 *                 how many cells will remain with values by the end of the function, and a valid gameState with an empty game board.
 *                 The function will try to randomly generate a board by randomly filling legal values in the amount of the first parameter,
 *                 solve the board, and keep values according to the second parameter, printing relevant message in the end of the process.
 * undo - The function needs a valid gameState with loaded game board and well maintained undo/redo list.
 *        The function tries to undo the current move in the list (if it exist), reverting all the values from the current game state to the values that were before the current move.
 * redo - The function needs a valid gameState with loaded game board and well maintained undo/redo list.
 *        The function tries to redo the last move that was undone (if it exist), reverting all the values from the current game state to the values that were before the undoing.
 * saveBoard - The function needs a valid gameState with a loaded and well maintained game board, and a file name.
 *             The function tries to save the current game board to the file given or create it if it doesn't exist. File path may be relative or absolute.
 * hintBoard - The function needs the column and row of a specific cell and a valid gameState with a loaded game board.
 *             The function tries to find a value that fit into some solution of the current puzzle, if a solution is possible and the cell is empty, and print it.
 * numOfSol - The function needs a valid gameBoard with loaded value in it.
 *            The function finds the amount of different possible solutions to the current game board and prints it.
 * autofill - The function needs a valid gameState with a loaded game board in it.
 *            The function fills values to any cell that has only single legal value that can be entered to it in the original board (before it starts filling values).
 *            May result in an erroneous board afterwards, since values entered by this function aren't taken into account when checking new cells.
 * resetGame - The function needs a valid gameState with a loaded game board in it and a well maintained undo/redo list.
 *             The function undoes any move that happened since the loading of the file, and resets the undo/redo list.
 * exitGame - The function needs a valid and well allocated gameState.
 *            The function frees any memory that is still in use by the program and exits completely.*/

#ifndef GAME_H_
#define GAME_H_
#include "gameStructs.h"

void startPuzzle(gameState *metaBoard, char *fileName, gameMode mode);
/* The function fills the gameBoard of the gameState metaBoard with the board that is saved in the file fileName by using the file handling module
 * or initialize an empty 3*3 board if no file was given. The gameMode of metaBoard will change to "mode" in this function only
 * if the file was opened correctly or there was no given file and the user entered Edit mode (empty 3*3 board).
 * INPUT: gameState *metaBoard - A valid gameState pointer that keeps information for the current game.
 *        char *fileName - An input string from the user, should contain a valid file name or path to a sudoku board file,
 *        or be empty if user wishes to edit an empty 3*3 board.
 *        gameMode mode - The mode the user wished to enter, will change the current mode of  metaBoard only if the new board was opened correctly.*/
void setBoard(int x, int y, int z, gameState *metaBoard, int set);
/*The function tries to set the value z in the cell <x,y> in the game board of the gameState metaBoard.
 *Value 0 erases the cell, fixed cells can't be changed, field filledCells of metaBoard updates accordingly, and the game board is printed after a successful move or an appropriate message if the move failed.
 *The function updates erroneous cells, undo/redo list, and gameMode in case the user is in solve mode and filled the puzzle successfully.
 *INPUT: int x,y - Integers representing the column and row of the cell the user wish to change by <x,y>.
 *		 int z - The value which we want to insert to the given cell, ranging from 0 (erase cell) to board length.
 *		 gameState *metaBoard - A pointer to a valid gameState with board gameBoard filled with numbers 0 to board length which we try to insert value z to in cell <x,y>.
 *		 int set - A boolean parameter used in order to indicate if we want to advance the undo/redo list (1) or not (0) when not needed eg. while doing undo/redo*/
int validate(gameState *metaBoard);
/*The function verifies the current gameBoard of gameState metaBoard is a valid board that can be completed by using ILP to solve it, and return a value accordingly.
 *INPUT: gameState *metaBoard - A pointer to a valid gameState with board gameBoard filled with valid values which we try to solve by using ILP.
 *OUTPUT: The function returns (-1) if the ILP (Gurobi) has failed, (0) on an unsolvable board, and (1) if a solution was found and the board is valid.*/
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
void saveBoard(gameState *metaBoard, char *fileName);
/*The function tries to save the current board in metaBoard to the file fileName. If we are in edit mode, and the board is erroneous or invalid, the file won't be saved.
 * INPUT: gameState *metaBoard - A valid gameState pointer that keeps information for the current game.
 *        char *fileName - An input string from the user, should contain a valid file name or path that the sudoku board will be saved to.*/
void hintBoard(int x, int y, gameState *metaBoard);
/*The function prints a hint of a possible value to the given cell <x,y>, by using ILP to find a board solution.
 *INPUT: int x,y - Integers representing the column and row of the cell the user want hint by <x,y>. Should not be fixed, or a hint won't be given and an appropriate message will be shown.
 *       gameState *metaBoard - A pointer to a gameState with allocated board with valid values, should not contain erroneous values or a hint won't be given and an appropriate message will be shown.*/
void numOfSol(board *gameBoard);
/*The function finds all the possible solutions to the game board using an exhaustive backtracking algorithm, and prints an appropriate message.
 * INPUT: board *gameBoard - A pointer to an allocated board with valid values we try to fill in every possible way using exhaustive backtracking and find all possible solutions.*/
void autofill(gameState *metaBoard);
/*The function tries to fill in the board each cell that has only valid value to enter, and prints appropriate messages.
 * INPUT: gameState *metaBoard - A pointer to a gameState with an allocated game board with valid values that the function will try to fill "obvious" values to.*/
void resetGame(gameState *metaBoard);
/*The function resets the game board in metaBoard to be the original board the user loaded, by reverting all the changes made using undo, and then clearing the undo/redo list.
 *INPUT: gameState *metaBoard - A pointer to a gameState with allocated undo/redo linked list and board with valid values in it.*/
void exitGame(gameState *metaBoard);
/*The function exits the game by freeing all the memory that still haven't been freed from gameState metaBoard, and terminates the program.
 *INPUT: gameState *metaBoard - A pointer to a gameState with allocated memory for linked list, board and cells that needs to be freed.*/

#endif /* GAME_H_ */
