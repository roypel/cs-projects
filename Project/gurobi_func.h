
#ifndef GUROBI_FUNC_H_
#define GUROBI_FUNC_H_

int findSol(int cols, int rows, int* filled, int amountFilled, double* sol);
/*Fills the board for ILP functions that need it,and keeps the solution in the sol array provided.
INPUT-int cols and int rows dimentions of the blocks,int* filled array contains the cells that are already filled in the board.int 
amountFilled contains the amount of these cells.double* sol contains The values of the cells in the solution for the board.For every 
cell there will be rows*cols spaces in the array allocated to it.The value of the cell in the solution will be its index from the 
rows*cols options.
OUTPUT-function returns 1 if there was a solution to the board,0 if there wasn't and -1 if an error occured*/

#endif /* GUROBI_FUNC_H_ */
