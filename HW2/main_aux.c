
#include <stdio.h>
#include <stdlib.h>

void printBoard(){

}

void getHeapSizes(int heaps[], int N){
	int heapSize = 0;
	int i;
	printf("Enter the heap sizes:\n");
	for (i = 0; i < N; i++){
		scanf("%d", &heapSize);
		if (heapSize <= 0){
			printf("Error: the size of heap %d should be positive.\n", i+1);
			exit(0);
		}
		heaps[i] = heapSize;
	}
}

int getNumberOfHeaps(){
	int N;
	printf("Enter the number of heaps:\n");
	scanf("%d",&N);
	if ((N < 1) || (N > 32)){
		printf("Error: the number of heaps must be between 1 and 32.\n");
		exit(0);
	}
	return N;
}
