/* Header file which contains the functions used to read and interpret the user input, and call the relevant function from the game module. Includes the following functions:
 * readInput - The function needs an allocated gameState.
 *             The function reads input from the user and executes them using different modules, while updating the gameState as needed.*/

#ifndef PARSER_H_
#define PARSER_H_
#include "gameStructs.h"

void readInput(gameState *metaBoard);
/*The function is the main flow of the game. It receives a gameState as input and manipulates and change it according to the user input commands and send it to the various other functions and modules.
 *The function assumes that input metaBoard is a pointer for a gameState with allocated memory for a game board and a linked list, and handle the changing states of the game by itself.
 *INPUT: gameState *metaBoard - A valid gameState pointer with preallocated board gameBoard and linked list.*/

#endif /* PARSER_H_ */
