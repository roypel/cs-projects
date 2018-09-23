/* Header file which contains the functions that we use in order to operate the stack struct. Includes the following functions:
 * pop - The function needs a pointer to a stackPointer.
 *       The function removes and returns the item that was in the top of the stack.
 * push - The function needs an item that would be added to the stack, and a pointer to a stackPointer.
 *        The function adds the new item to the top of the stack.*/

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
