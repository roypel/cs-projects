#ifndef STACKFUNC_H_
#define STACKFUNC_H_

item pop(stack stack);
/*When we reached bottom (stack.stack->val == -1) we have finished exhausting the backtracking*/
void push(item newItem, stack stack);

#endif /* STACKFUNC_H_ */
