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
	printf("Sudoku\n------\n");
	metaBoard.gameBoard = (board *) calloc(1, sizeof(board));/*We use calloc in order to reset the values of gameBoard so it will be Null\0 as needed*/
	if (metaBoard.gameBoard == NULL) {
		printf("Error: calloc has failed\n");
		exit(0);
	}
/*	metaBoard.solution = (board *) malloc(sizeof(board));
	if (metaBoard.solution == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}*/
	metaBoard.mode = Init;
	metaBoard.moves = (linkedList *) malloc(sizeof(linkedList));
	if (metaBoard.moves == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard.moves->currentMove = (node *) malloc(sizeof(node));
	if (metaBoard.moves->currentMove == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard.moves->currentMove->change = (int *) malloc(sizeof(int));
	if (metaBoard.moves->currentMove->change == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard.moves->currentMove->change[0] = -1;
	metaBoard.moves->currentMove->next = NULL;
	metaBoard.moves->firstNode = metaBoard.moves->currentMove;
	metaBoard.markError = 1;
	readInput(&metaBoard);
	return 0;
}
