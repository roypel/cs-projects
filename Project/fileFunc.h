/* Header file which contains functions that are used in order to read from files containing boards or creating new files containing boards. Including the functions:
 * saveToFile - The function needs a valid gameState with a loaded game board and a file path the may be relative or absolute.
 *              The function tries to save the current state of the game board to the file name provided, or create a new one if it doesn't exists yet.
 * sendToFill - The function needs a valid gameState, a file name of a sudoku board with valid values and a valid gameMode.
 *              The function tries to fill the gameState game board with the values in the file and then prints the board, or print an error message if there was a problem.*/

#ifndef FILEFUNC_H_
#define FILEFUNC_H_

void saveToFile(gameState *metaBoard, char *fileName);
/* The function tries to save the current board in metaBoard to the file fileName. If the file can't be created or modified, the file won't be saved.
 * INPUT: gameState *metaBoard - A valid gameState pointer that keeps information for the current game.
 *        char *fileName - An input string from the user, should contain a valid file name or path that the sudoku board will be saved to.*/
void sendToFill(gameState *metaBoard, char *fileName, gameMode mode);
/* The function fills the gameBoard of the gameState metaBoard with the board that is saved in the file fileName by using the function
 * fillBoard, or initialize an empty 3*3 board if no file was given. The gameMode of metaBoard will change to "mode" in this function only
 * if the file was opened correctly or ther ewas no given file and the user entered Edit mode (empty 3*3 board).
 * INPUT: gameState *metaBoard - A valid gameState pointer that keeps information for the current game.
 *        char *fileName - An input string from the user, should contain a valid file name or path to a sudoku board file,
 *        or be empty if user wishes to edit an empty 3*3 board.
 *        gameMode mode - The mode the user wished to enter, will change the current mode of  metaBoard only if the new board was opened correctly.*/

#endif /* FILEFUNC_H_ */
