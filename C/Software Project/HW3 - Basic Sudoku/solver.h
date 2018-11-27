#ifndef SOLVER_H_
#define SOLVER_H_
#include "gameStructs.h"

int solver(board *tmpBoard, int index);
void builder(board *buildBoard, int x, int y);
void hinter(gameState *metaBoard);

#endif /* SOLVER_H_ */
