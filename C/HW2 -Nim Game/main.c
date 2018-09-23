#include "main_aux.h"
#include "sp_nim.h"
#include <stdio.h>
#include <stdlib.h>
#include "SPBufferset.h"
#define MAX_HEAPS 32 /*Maximum number of heaps*/

int main(){
	int N;
	int heaps[MAX_HEAPS] = {0};
	int turn = 1;
	SP_BUFF_SET();
	N = getNumberOfHeaps();/*Actual heaps used*/
	getHeapSizes(heaps, N);
	while (checkWinner(heaps, N)){/*Continue with the game until someone wins*/
		printTurn(turn, heaps, N);/*Printing turn stats*/
		if (turn % 2){/*On an odd turn, the user plays*/
			printUserTurn(heaps, N);
		}
		else/*On even turns, computer plays*/
			nextMove(heaps, N);
		turn++;
	}
	printWinner(turn);
	return 0;
}
