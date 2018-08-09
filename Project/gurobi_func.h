/*
 * gurobi_func.h
 *
 *  Created on: Aug 6, 2018
 *      Author: Lenovo
 */

#ifndef GUROBI_FUNC_H_
#define GUROBI_FUNC_H_

int fillboard(int cols, int rows, int* filled);
/*fills the board for ILP functions which need it.filled is the cells that are already filled in the board,will be empty if we use a
function that only works on empty board(generate,etc.) and might not be empty on functions that can work on boards that are not empty
(hint,etc.).doesnt revert the board back to the original state,so the boards need to be reverted back to it's original state if the
the command that requested it is hint,etc and not reverted back if that command is generate.*/

#endif /* GUROBI_FUNC_H_ */
