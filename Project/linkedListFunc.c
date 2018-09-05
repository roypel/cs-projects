#include <stdio.h>
#include <stdlib.h>
#include "gameStructs.h"
#include "MainAux.h"

void removeAllNext(node *head) {/*Removes the moves after this move from the undo/redo list*/
	if (head != NULL) {
		removeAllNext(head->next);
		head->next = NULL;
		free(head->change);
		free(head);
	}
}

node* addNextMove(node *currentMove, int *move, int numOfMoves) { /*Adds the new move to the undo/redo list and deletes the moves
	that come after the current move in the undo/redo list if needed(if they exist)*/
	int i;
	node *newMove = (node*) malloc(sizeof(node));
	checkInitalize(newMove, "malloc");
	newMove->change = (int*) malloc(sizeof(int) * (4 * numOfMoves + 1));
	checkInitalize(newMove->change, "malloc");
	newMove->change[0] = numOfMoves;
	for (i = 1; i <= numOfMoves * 4; i++) {
		newMove->change[i] = move[i - 1];/*Insert the x y z1 z2 values of the changes to the array of changes in the current move*/
	}
	newMove->next = NULL;
	if (currentMove != NULL) {/*Is the undo/redo list not empty?*/
		if (currentMove->next != NULL)/*Is there a next move?*/
			removeAllNext(currentMove->next);
		newMove->prev = currentMove;
		currentMove->next = newMove;
	} else
		newMove->prev = NULL;
	return newMove;
}
