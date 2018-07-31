#include <stdlib.h>
#include "gameStructs.h"

item pop(stack stack){
	item top = *stack.stack;
	if (stack.stack->val != -1){/*This symbolizes we reached the end of the stack (only bottom has val = -1)*/
		stack.stack = (item*)realloc(stack.stack, sizeof(stack.stack) - sizeof(item));
	}
	return top;
}

void push(item newItem, stack stack){
	stack.stack = (item*)realloc(stack.stack, sizeof(stack.stack)+sizeof(item));
	*stack.stack = newItem;
}
