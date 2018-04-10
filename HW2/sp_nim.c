#include <stdio.h>
#include "main_aux.h"

int checkWinner(int heaps[], int N) {
	/*The function checks if all the heaps are empty, and if so the game should end*/
	int i;
	for (i = 0; i < N; i++) {
		if (heaps[i] != 0)
			break;/*Found a non-empty heap*/
	}
	if (i == N) {
		return 0;
	}
	return 1;
}

int calculateNimSum(int heaps[], int N) {
	/*The function calculates the nim-sum of all the heaps by XOR-ing all the values together*/
	int nimSum = heaps[0];
	int i;
	for (i = 1; i < N; i++) {
		nimSum ^= heaps[i];
	}
	return nimSum;
}

void nextMove(int heaps[], int N){
	/*The function calculates and play the next move for the computer*/
	int nimSum = calculateNimSum(heaps, N);
	int i;
	if (nimSum == 0) {
		for (i = 0; i < N; i++) {
			if (heaps[i] > 0) {
				heaps[i]--;
				printComputerTurn(i+1, 1);
				break;/*Found the minimum non-empty heap*/
			}
		}
	} else {
		for (i = 0; i < N; i++) {
			if ((heaps[i] ^ nimSum) < heaps[i]){
				printComputerTurn(i+1, heaps[i]-(heaps[i] ^ nimSum));
				heaps[i] = heaps[i] ^ nimSum;
				break;/*Found the minimum heap with enough tokens to remove*/
			}
		}
	}
}
