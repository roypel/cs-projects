#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "MainAux.h"
#include "gameStructs.h"
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
	metaBoard.moves->currentMove->change[0] = -1;
	metaBoard.moves->currentMove->next = NULL;
	metaBoard.moves->firstNode = metaBoard.moves->currentMove;
	metaBoard.markError = 1;
	readInput(&metaBoard);
	return 0;
}
