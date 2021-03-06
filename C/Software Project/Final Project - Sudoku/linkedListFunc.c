/* Source file which contains the functions that we use in order to add\remove items from the struct that contains the moves that occurred
 * in the game, which is implemented as a doubly linked list. Includes the following functions:
 * removeAllNext - A function which deletes from the list and frees from memory the move that was sent to it as a parameter
 *                 and all the moves that occurred afterwards.
 * addNextMove - A function that is used to add a new node to the list with the data that was sent to it and returns the node,
 *               while also removing all the moves that were kept after the current move in the process.*/

#include <stdio.h>
#include <stdlib.h>
#include "gameStructs.h"
#include "mainAux.h"

void removeAllNext(node *head) {
	if (head != NULL) {
		removeAllNext(head->next);
		head->next = NULL;
		free(head->change);
		free(head);
	}
}

node* addNextMove(node *currentMove, int *move, int numOfMoves) {
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
	if (currentMove != NULL) {
		if (currentMove->next != NULL)
			removeAllNext(currentMove->next);
		newMove->prev = currentMove;
		currentMove->next = newMove;
	} else
		newMove->prev = NULL;
	return newMove;
}
