#ifndef SOLVER_H_
#define SOLVER_H_

int solver(int **board, int cols, int rows, int index);
void builder(int cols, int rows, int **board, int x, int y);
void hinter(int hints, int cols, int rows, int **board);

#endif /* SOLVER_H_ */
