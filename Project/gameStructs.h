#ifndef GAMESTRUCTS_H_
#define GAMESTRUCTS_H_

typedef struct cell {/*The information about each cell in the board.*/
	int value;
	int fixed;
	int error;
} cell;

typedef struct board {/*Information about the board.*/
	cell **board;
	int cols;
	int rows;
} board;

typedef enum gameMode {/*The three game modes, used for functions wanting to know the current state of the game.*/
	Init, Solve, Edit
} gameMode;

typedef struct node {/*Struct that contains the information that happened in a move, and points to the move before and after it.*/
	int *change;
	struct node *next;
	struct node *prev;
} node;

typedef struct linkedList {/*The linked list that contains the moves, with a pointer to the first move for functions that need it such as undo.*/
	node *firstNode;
	node *currentMove;
} linkedList;

typedef struct item {/*Contains the index of the cells stored in the stack for num_solutions
					  	although it currently contains only one field (we found it was the best way to save memory), it is kept for future modularity.*/
	int index;
} item;

typedef struct stackPointer {/*A pointer for the stack of items with the necessary information.*/
	item *stack;
	int size;
	int maxSize;
} stackPointer;

typedef struct gameState {/*Struct that contains the necessary information for the game-the board, the current mode, should we mark
                            errors or not, the moves linkedlist, the amount of filledCells and the cols and rows in each block.*/
	board *gameBoard;
	gameMode mode;
	int markError;
	linkedList *moves;
	int filledCells;
	int cols;
	int rows;
} gameState;

#endif /* GAMESTRUCTS_H_ */
