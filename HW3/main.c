#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "MainAux.h"
#include "SPBufferset.h"

int main(int argc, char *argv[]){
	SP_BUFF_SET();
	if (argc < 2)
		srand(4);
	else
		srand(getSeed(argv[1]));
	readInput();
	return 0;
}
