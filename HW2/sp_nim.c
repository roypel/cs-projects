#include <stdio.h>
#include "main_aux.h"

int checkWinner(int heaps[], int N) {
	int i;
	for (i = 0; i < N; i++) {
		if (heaps[i] != 0)
			break;
	}
	if (i == N) {
		return 0;
	}
	return 1;
}

int calculateNimSum(int heaps[], int N) {
	int nimSum = heaps[0];
	int i;
	for (i = 1; i < N; i++) {
		nimSum ^= heaps[i];
	}
	return nimSum;
}

void nextMove(int heaps[], int N){
	int nimSum = calculateNimSum(heaps, N);
	int i;
	if (nimSum == 0) {
		for (i = 0; i < N; i++) {
			if (heaps[i] > 0) {
				heaps[i]--;
				printComputerTurn(i+1, 1);
				break;
			}
		}
	} else {
		for (i = 0; i < N; i++) {
			if ((heaps[i] ^ nimSum) < heaps[i]){
				printComputerTurn(i+1, heaps[i]-(heaps[i] ^ nimSum));
				heaps[i] = heaps[i] ^ nimSum;
				break;
			}
		}
	}
}
