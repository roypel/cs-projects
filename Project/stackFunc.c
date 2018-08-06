#include <stdlib.h>
#include <stdio.h>
#include "gameStructs.h"

item pop(stackPointer *stack) {
	item top = *(stack->stack + (sizeof(item) * stack->size));
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
	int i;
	item *top, *temp;/*Will save the address of new space (top of stack)*/
	if (stack->size == stack->maxSize) {
		stack->maxSize *= 2;
		printf("max %d, size %d\n", stack->maxSize, stack->size);
		stack->stack = realloc(stack->stack, stack->maxSize * sizeof(item));/*Resize the stack to double size*/
		if (stack->stack == NULL) {
			printf("Error: realloc has failed\n");
			exit(0);
		}
	}
	printf("max %d, size %d\n", stack->maxSize, stack->size);
	top = stack->stack + (sizeof(item) * stack->size);/*Point top to top of stack*/
	printf("here\n");
	if (stack->size == 15) {
		for (i = 0; i <= 17; i++) {
			printf("i : %d\n",i);
			temp = stack->stack + (sizeof(item) * i);
			printf("%d\n", (int)sizeof(item));
			printf("col %d row %d val %d i %d\n", temp->col, temp->row,
					temp->val, i);
		}
	}
	*top = newItem;/*Add new item at the top of stack*/
	printf("there\n");
	stack->size++;
}
