#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "MainAux.h"
#include "gameStructs.h"
#include "SPBufferset.h"

int main(int argc, char *argv[]){
	gameState *metaBoard;
	SP_BUFF_SET();
	if (argc < 2)
		srand(4);
	else
		srand(getSeed(argv[1]));
	readInput(metaBoard);
	return 0;
}
