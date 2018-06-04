#ifndef PARSER_H_
#define PARSER_H_
#include "gameStructs.h"

void readInput(gameState *metaBoard);
/*The function is the main flow of the game. It receives a gameState as input and manipulates and change it according to the user input command and send it to the various other functions and modules.
 *The function assumes that input metaBoard is a pointer for a gameState with allocated memory for two boards, and handle the readings of the size of the boards, initialization and changing the states of the game by itself.
 *INPUT: gameState *metaBoard - A valid gameState pointer with preallocated boards gameBoard and solution.*/
void readBoard(gameState *metaBoard);
/*The function handles the user input for current game board size (in this assignment it's always 3) and number of hints (fixed cells) the user wishes to play.
 *The function will continue only if a valid input for cells is entered and updates metaBoard with the needed values. It's assumed that the input includes only one integer, blank spaces will be regarded as 0.
 *INPUT: gameState *metaBoard - A valid gameState pointer with preallocated boards gameBoard and solution.*/

#endif /* PARSER_H_ */
