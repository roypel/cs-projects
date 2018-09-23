/*Source of the main file in the program that allocate the necessary memory to start a game*/

#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "gameStructs.h"
#include "mainAux.h"
#include "SPBufferset.h"

int main() {
	gameState metaBoard;
	SP_BUFF_SET()
	;
	srand(time(NULL));
	printf("Sudoku\n------\n");
	metaBoard.gameBoard = (board *) calloc(1, sizeof(board));/*We use calloc in order to reset the values of gameBoard so it will be Null\0 as needed*/
	checkInitalize(metaBoard.gameBoard, "calloc");
	metaBoard.mode = Init;
	metaBoard.moves = (linkedList *) malloc(sizeof(linkedList));
	checkInitalize(metaBoard.moves, "malloc");
	metaBoard.moves->currentMove = (node *) malloc(sizeof(node));
	checkInitalize(metaBoard.moves->currentMove, "malloc");
	metaBoard.moves->currentMove->change = (int *) malloc(sizeof(int));
	checkInitalize(metaBoard.moves->currentMove->change, "malloc");
	metaBoard.moves->currentMove->prev = metaBoard.moves->currentMove->next = NULL;
	metaBoard.moves->firstNode = metaBoard.moves->currentMove;/*Will indicate the beginning of the list, as a sentinel*/
	metaBoard.markError = 1;/*Setting the default value of mark errors to 1*/
	readInput(&metaBoard);
	return 0;
}
