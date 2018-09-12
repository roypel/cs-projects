/*Header file which contains the functions that we use in order to add\remove items from the struct that contains the moves that occured
in the game,which is implemented as a doubly linked list*/

#ifndef LINKEDLISTFUNC_H_
#define LINKEDLISTFUNC_H_

void removeAllNext(node *head);
/* The function frees all the memory allocated by all the nodes in the linked list after the node head, starting from the tail.
 * INPUT: node *head - A pointer of a node in the undo/redo linked list, that all the nodes from this node to the tail will be freed from memory.*/
node* addNextMove(node *currentMove, int *move, int numOfMoves);
/* The function builds a new move for the undo/redo list, according to the parameters it receives, and adds it as the new tail for the list after the currentMove.
 * INPUT: node *currentMove - A pointer of a node in the undo/redo linked list, where the user currently at. The user can redo to moves after this node or undo to moves before this node, if exists.
 *        int *move - An array of integers for all the changes that were made in the last move, eacg change takes 4 cells in the array in the format x y z1 z2, where z1 is the previous value in the cell x y and z2 is the new value.
 *        int numOfMoves - The number of total moves that was entered to the move array.
 * OUTPUT: Pointer to the new node that was made in this function, to update currentMove if necessary.*/
#endif /* LINKEDLISTFUNC_H_ */
