/* Header file which contains the functions that we use in order to add\remove items from the struct that contains the moves that occurred in the game. Includes the following functions:
 * removeAllNext - The function needs a pointer to a node of a move, preferably a one inside the undo/redo list in the game.
 *                 The function frees all the memory allocated for the node and all the nodes after it in the list.
 * addNextMove - The function needs a pointer to the node of the current move in the game, an int array that fits to a move format
 *               (as stated in gameStructs.h, in the node section) and the number of moves that stored in the array.
 *               The function adds the array to a node, add it as the end of the list after the current move, and return a pointer to
 *               it so it can be saved as the new current move.*/

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
