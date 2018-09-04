#ifndef FILEFUNC_H_
#define FILEFUNC_H_

void saveFile(gameState *metaBoard, char *fileName);
/* The function tries to save the current board in metaBoard to the file fileName. If the file can't be created or modified,
 * or we are in edit mode, and the board is erroneous or invalid, the file won't be saved.
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
