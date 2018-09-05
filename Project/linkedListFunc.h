#ifndef LINKEDLISTFUNC_H_
#define LINKEDLISTFUNC_H_

void removeAllNext(node *head);/*Removes the moves after this move from the undo/redo list*/
node* addNextMove(node *currentMove, int *move, int numOfMoves);/*Adds the new move to the undo/redo list and deletes the moves
	that come after the current move in the undo/redo list if needed(if they exist)*/

#endif /* LINKEDLISTFUNC_H_ */
