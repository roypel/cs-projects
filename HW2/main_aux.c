#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void getHeapSizes(int heaps[], int N) {
	/*The function updates the heap array with the sizes the user inputs.
	 * if the user inputs a non-postive number or a non-digit, the program terminates.*/
	int heapSize = 0;
	int i;
	printf("Enter the heap sizes:\n");
	for (i = 0; i < N; i++) {
		if (scanf(" %d", &heapSize)) {
			if (heapSize <= 0) {
				printf("Error: the size of heap %d should be positive.\n",
						i + 1);
				exit(0);
			}
			heaps[i] = heapSize;
		} else {/*Input isn't digits*/
			printf("Error: the size of heap %d should be positive.\n", i + 1);
			exit(0);
		}
	}
}

int getNumberOfHeaps() {
	/*The function returns the number of heaps for the upcoming game.
	 *Values allowed are only between 1 and 32, or else the program terminates.*/
	int N;
	printf("Enter the number of heaps:\n");
	scanf(" %d", &N);
	if ((N < 1) || (N > 32)) {
		printf("Error: the number of heaps must be between 1 and 32.\n");
		exit(0);
	}
	return N;
}

void printWinner(int turn) {
	/*The function prints a message of who won the game and terminates the program*/
	if (turn % 2 == 0) {
		printf("You win!\n");
		exit(0);
	}
	printf("Computer wins!\n");
	exit(0);
}

void printTurn(int turn, int heaps[], int N) {
	/*The function prints the current stats of the game board*/
	int i;
	printf("In turn %d heap sizes are:", turn);
	for (i = 0; i < N; i++) {
		printf(" h%d=%d", i + 1, heaps[i]);
	}
	printf(".\n");
}

void printUserTurn(int heaps[], int N) {
	/*The function reads the user input for his turn and prints messages accordingly*/
	int tempHeap;
	int tokens;
	int notValid = 1;/*A flag variable to record if the input was valid*/
	printf(
			"Your turn: please enter the heap index and the number of removed objects.\n");
	while (notValid) {
		tokens = 0;
		tempHeap = 0;/*Reset the input values before reading new input*/
		scanf(" %d %d", &tempHeap, &tokens);
		if ((tempHeap > N) || (tempHeap < 1) || (tokens < 1)
				|| (tokens > heaps[tempHeap - 1]))/*Check if the move is possible*/
			printf(
					"Error: Invalid input.\nPlease enter again the heap index and the number of removed objects.\n");
		else
			notValid = 0;
	}
	heaps[tempHeap - 1] -= tokens;
	printf("You take %d objects from heap %d.\n", tokens, tempHeap);
}

void printComputerTurn(int heap, int token) {
	/*The function prints the computer move*/
	printf("Computer takes %d objects from heap %d.\n", token, heap);
}
