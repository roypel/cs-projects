#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "MainAux.h"
#include "gameStructs.h"
#include "SPBufferset.h"

int main() {
	gameState metaBoard;
	printf("Sudoku\n------\n");
	metaBoard.gameBoard = (board *) malloc(sizeof(board));
	if (metaBoard.gameBoard == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard.solution = (board *) malloc(sizeof(board));
	if (metaBoard.solution == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
	}
	metaBoard.mode = Init;
	SP_BUFF_SET()
	;
	readInput(&metaBoard);
	return 0;
}
