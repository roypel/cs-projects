#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*int checkInput(){
 char c;
 int i;
 int number;
 for (i = 0; isspace((c = getchar())); i++) {
 if (!isdigit(c)) {
 return -1;
 if (flag) {
 input[numOfDigits] = c;
 numOfDigits++;
 } else {
 if (c != '0') {
 flag = 1;
 input[numOfDigits] = c;
 numOfDigits++;
 }
 }
 } else
 break;
 }
 }
 */
void getHeapSizes(int heaps[], int N) {
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
		} else {
			printf("Error: the size of heap %d should be positive.\n", i + 1);
			exit(0);
		}
	}
}

int getNumberOfHeaps() {
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
	if (turn % 2 == 0) {
		printf("Computer wins!\n");
		exit(0);
	}
	printf("You win!\n");
}

void printTurn(int turn, int heaps[], int N) {
	int i;
	printf("In turn %d heap sizes are:", turn);
	for (i = 0; i < N; i++) {
		printf(" h%d=%d", i + 1, heaps[i]);
	}
	printf(".\n");
}

void printUserTurn(int heaps[], int N) {
	int tempHeap;
	int tokens;
	int flag = 1;
	printf(
			"Your turn: please enter the heap index and the number of removed objects.\n");
	while (flag) {
		fflush(stdin);
		if (scanf(" %d", &tempHeap)) {
			fflush(stdin);
			if (scanf(" %d", &tokens)) {
				if ((tempHeap > N) || (tempHeap < 1) || (tokens < 1)
						|| (tokens > heaps[tempHeap - 1]))
					printf(
							"Error: Invalid input.\nPlease enter again the heap index and the number of removed objects.\n");
				else
					flag = 0;
			}
		}
	}
	heaps[tempHeap - 1] -= tokens;
	printf("You take %d objects from heap %d.\n", tokens, tempHeap);
}

void printComputerTurn(int heap, int token) {
	printf("Computer takes %d objects from heap %d.\n", token, heap);
}
