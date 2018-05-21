
#ifndef GAME_H_
#define GAME_H_
#include "gameStructs.h"

void setBoard(int x, int y, int z, gameState *metaBoard);
int checkCell(int x, int y, int z, board *check);
int hintBoard(int x, int y, board *sol);
void exitGame(gameState *metaBoard);
void generateBoard(gameState *metaBoard);
void validate(gameState *metaBoard);
void initalizeBoard(board *newBoard);
void initalizeGame(gameState *metaBoard);

#endif /* GAME_H_ */
