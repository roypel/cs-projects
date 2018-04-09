#include "main_aux.h"
#include "sp_nim.h"
#include <stdio.h>
#include <stdlib.h>
#include "SPBufferset.h"
/*#define N getNumberOfHeaps() N=Number of heaps, the macro calls the function in the main_aux file*/

int main(){
	int N;
	int *heaps;
	int turn = 1;
	int i;
	SP_BUFF_SET();
	N = getNumberOfHeaps();
	heaps = calloc(N, sizeof(int));
	for (i = 0; i < N; i++)
		heaps[i] = 0;
	getHeapSizes(heaps, N);
	while (checkWinner(heaps, N)){
		printTurn(turn, heaps, N);
		if (turn % 2){
			printUserTurn(heaps, N);
		}
		else
			nextMove(heaps, N);
		turn++;
	}
	printWinner(turn);
	free(heaps);
	return 0;
}
