#include <stdio.h>
#include <stdlib.h>
#include "gameStructs.h"

void removeAllNext(node *head) {
	if (head != NULL)
		removeAllNext(head->next);
	free(head->change);
	free(head);
}

node* addNextMove(node *currentMove, int *move, int numOfMoves) {
	int i;
	node *newMove = (node*) malloc(sizeof(node));
	newMove->change = (int*) malloc(sizeof(int) * 4 * numOfMoves + 1);
	newMove->change[0] = numOfMoves;
	for (i = 1; i <= numOfMoves * 4; i++) {
		newMove->change[i] = move[i];/*Insert the x y z1 z2 values of the changes to the array of changes in the current move*/
	}
	newMove->next = NULL;
	if (currentMove != NULL) {
		if (currentMove->next != NULL)
			removeAllNext(currentMove->next);
		newMove->prev = currentMove;
		currentMove->next = newMove;
	} else
		newMove->prev = NULL;
	return newMove;
}
