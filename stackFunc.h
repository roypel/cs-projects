/*Header file which contains the functions that we use in order to operate the stack struct for the num_solutions command*/

#ifndef STACKFUNC_H_
#define STACKFUNC_H_

item pop(stackPointer *stack);
/* The function returns the item that is on the top of the stack that was received as input, and removes the item from the stack. Adjust the stack size if necessary.
 * INPUT: stackPointer *stack - A pointer to a stackPointer that has a pointer to a stack we wish to remove and return the top item from.
 * OUTPUT: The item that was on the top of the stack and was removed from it.*/
void push(item newItem, stackPointer *stack);
/* The function adds a new item to the top of the stack, resizing it if necessary.
 * INPUT: item newItem - An item we will add to the top of the stack that's in the stackPointer stack
 *        stackPointer *stack - A pointer to a stackPointer that has a pointer to a stack we wish to add the new item on top of.*/

#endif /* STACKFUNC_H_ */
