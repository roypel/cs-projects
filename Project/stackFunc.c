#include <stdlib.h>
#include <stdio.h>
#include "gameStructs.h"

item pop(stackPointer *stack) {
	item top = *(stack->stack + stack->size - 1);
	if (stack->size <= stack->maxSize * 0.25) {/*Resize the stack to half size to save space*/
		stack->maxSize /= 2;
		stack->stack = (item*) realloc(stack->stack,
				stack->maxSize * sizeof(item));/*Resize the stack*/
		if (stack->stack == NULL) {
			printf("Error: realloc has failed\n");
			exit(0);
		}
	}
	stack->size--;
	return top;
}

void push(item newItem, stackPointer *stack) {
	item *top;/*Will save the address of new space (top of stack)*/
	if (stack->size == stack->maxSize) {
		stack->maxSize *= 2;
		stack->stack = realloc(stack->stack, stack->maxSize * sizeof(item));/*Resize the stack to double size*/
		if (stack->stack == NULL) {
			printf("Error: realloc has failed\n");
			exit(0);
		}
	}
	top = stack->stack + stack->size;/*Point top to top of stack*/
	*top = newItem;/*Add new item at the top of stack*/
	stack->size++;
}
