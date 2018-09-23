#ifndef GAMESTRUCTS_H_
#define GAMESTRUCTS_H_

typedef struct cell{
	int value;
	int fixed;
} cell;

typedef struct board{
	cell **board;
	int cols;
	int rows;
} board;

typedef struct gameState{
	board *gameBoard;
	board *solution;
	int filledCells;
	int cols;
	int rows;
} gameState;

#endif /* GAMESTRUCTS_H_ */
