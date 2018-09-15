/* Header file which contains the structs and enums that are defined and used in this program.
 * gameMode - Used to hold the different game modes, Init, Solve and Edit.
 * cell - Used to keep information on any cell in the game board, holds the value, and an indicator (0 or 1) if the cell is fixed or erroneous.
 * board - Used to keep information about a game board, holds a 2D array of cells, and the amount of cells in each column and row in a block in the board.
 * node - Used to hold information on each move that changed the game state, holds an array with values indicating the change in the game state in this move, and the
 *        next and previous changes that were made, if they exists. The array is in the next format: the first cell indicates the amount of cells changed,
 *        and each change takes 4 spaces indicating the column and row of the cell changed, the previous value and the new value.
 * linkedList - Used to hold the information for the undo/redo list as a doubly linked list, holds a pointer
 *              to a sentinel for an indication on an empty list, and a pointer for the current move in the list.
 * item - Used to keep information for an item in the stack, holds an index of a cell. Kept for modularity and ease in future changes.
 * stackPointer - Used to keep informataion on a stack of items, holds a pointer to an array of items, it's current size, and it's currently allocated maximum size.
 * gameState - Used to hold information on a game, holds a pointer to a game board, an indicator of the current gameMode, indicator of the mark errors
 *             command (1 - show errors in solve mode, 0 - don't show errors on solve mode), a pointer to undo/redo linked list, indicator of
 *             the amount of current filled cells in the board, and the amount of cells in each column and row in a block in the board.*/

#ifndef GAMESTRUCTS_H_
#define GAMESTRUCTS_H_

typedef enum gameMode {/*The three game modes, used for functions wanting to know the current state of the game.*/
	Init, Solve, Edit
} gameMode;

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
