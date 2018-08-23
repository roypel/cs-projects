/* This example formulates and solves the following simple MIP model:
 maximize    x +   y + 2 z
 subject to  x + 2 y + 3 z <= 4
 x +   y       >= 1
 x, y, z binary
 */

#include <stdlib.h>
#include <stdio.h>

#include "gameStructs.h"
#include "gurobi_c.h"

void free_stuffs(int* ind, double* val, char* vtype) {
	free(ind);
	free(val);
	free(vtype);
}

int fillboard(int cols, int rows, int* filled, int amountFilled, double* sol) {/*return -1 on failure,1/integer on success*/
	/*also need to return the solution of the filled board,so find howto optimally*/
	/*sol will hold which cells contain which numbers. We want to return the solution and to free it, so we allocate it outside and free it outside so we can return inside*/
	int i, j, k, a, l;
	GRBenv *env = NULL;
	GRBmodel *model = NULL;
	int error = 0;
	int* ind;/*Which variable are used in each constraint*/
	double* val;/*The coefficients of the constraints*/
	double obj[1] = { 0 };
	char* vtype;/*What type the variable will be (all will be binary)*/
	int optimstatus;
	double objval;
	ind = (int*) calloc(cols * rows, sizeof(int));
	val = (double*) calloc(cols * rows, sizeof(double));
	vtype = (char*) calloc(cols * rows * cols * rows * cols * rows,
			sizeof(char));

	/* Create environment - log file is mip1.log */
	error = GRBloadenv(&env, "mip1.log");
	if (error) {
		printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/*not sure which one of the next 2 cancels unneeded prints,check it,probably both are exactly the same*/
	/*Cancel log being written to console*/
	error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
	if (error) {
		printf("ERROR %d GRBsetintparam(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}
	/*This too?*/
	error = GRBsetintparam(env, "OutputFlag", 0);
	if (error) {
		printf("ERROR %d GRBsetintparam(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/* Create an empty model named "mip1" */
	error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
	if (error) {
		printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/* Add variables */

	/* set the variables to be binary */
	for (i = 0; i < cols * rows; i++) {
		for (j = 0; j < cols * rows; j++) {
			for (k = 0; k < cols * rows; k++) {
				vtype[i * cols * rows * cols * rows + j * cols * rows + k] =
				GRB_BINARY;
			}
		}
	}

	/* add variables to model */
	error = GRBaddvars(model, cols * rows * cols * rows * cols * rows, 0, NULL,
	NULL, NULL, obj, NULL, NULL, vtype,
	NULL);
	if (error) {
		printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/* Change objective sense to maximization */
	error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
	if (error) {
		printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/* update the model - to integrate new variables */

	error = GRBupdatemodel(model);
	if (error) {
		printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/*only one number per cell constraints*/
	for (i = 0; i < cols * rows; i++) {
		for (j = 0; j < cols * rows; j++) {
			for (k = 0; k < cols * rows; k++) {
				ind[k] = i * cols * rows * cols * rows + j * cols * rows + k;
				val[k] = 1;
			}
			error = GRBaddconstr(model, cols * rows, ind, val, GRB_EQUAL, 1.0,
			NULL);/*constraint name is defaulted because we dont
			 care what it's name is*/
			if (error) {
				printf("ERROR %d in cell constraints GRBaddconstr(): %s\n",
						error, GRBgeterrormsg(env));
				free_stuffs(ind, val, vtype);
				return -1;
			}
		}
	}
	/*same number only once per row constraints*/
	for (i = 0; i < cols * rows; i++) {
		for (k = 0; k < cols * rows; k++) {
			for (j = 0; j < cols * rows; j++) {
				ind[j] = i * cols * rows * cols * rows + j * cols * rows + k;
				val[j] = 1;
			}
			error = GRBaddconstr(model, cols * rows, ind, val, GRB_EQUAL, 1.0,
			NULL);/*constraint name is defaulted because we dont
			 care what it's name is*/
			if (error) {
				printf("ERROR %d in row constraints GRBaddconstr(): %s\n",
						error, GRBgeterrormsg(env));
				free_stuffs(ind, val, vtype);
				return -1;
			}
		}
	}
	/*same number only once per col constraints*/
	for (j = 0; j < cols * rows; j++) {
		for (k = 0; k < cols * rows; k++) {
			for (i = 0; i < cols * rows; i++) {
				ind[i] = i * cols * rows * cols * rows + j * cols * rows + k;
				val[i] = 1;
			}
			error = GRBaddconstr(model, cols * rows, ind, val, GRB_EQUAL, 1.0,
			NULL);/*constraint name is defaulted because we dont
			 care what it's name is*/
			if (error) {
				printf("ERROR %d in col constraints GRBaddconstr(): %s\n",
						error, GRBgeterrormsg(env));
				free_stuffs(ind, val, vtype);
				return -1;
			}
		}
	}
	for (i = 0; i < cols; i++) {/*block row index*/
		for (j = 0; j < rows; j++) {/*block col index*/
			for (k = 0; k < rows * cols; k++) {/*cell number index*/
				for (l = 0; l < rows; l++) {/*cell row index*/
					for (a = 0; a < cols; a++) {/*cell col index*/
						ind[i] = (i + l) * cols * rows * cols * rows
								+ (j + a) * cols * rows + k;
						val[i] = 1;
					}
				}
				error = GRBaddconstr(model, cols * rows, ind, val, GRB_EQUAL,
						1.0, NULL);/*constraint name is defaulted because we dont
						 care what it's name is*/
				if (error) {
					printf("ERROR %d in block constraints GRBaddconstr(): %s\n",
							error, GRBgeterrormsg(env));
					free_stuffs(ind, val, vtype);
					return -1;
				}
			}
		}
	}
	/*cells already filled constraints*/
	for (i = 0; i < amountFilled; i++) {/*data is in col row val triplets*/
		ind[0] = filled[i * 3] * cols * rows
				+ filled[(i * 3) + 1] * cols * rows * cols * rows
				+ filled[(i * 3) + 2];/*+0 is the col,+1 is the row,+2 is the value*/
		val[0] = 1;
		error = GRBaddconstr(model, 1, ind, val, GRB_EQUAL, 1.0, NULL);/*constraint name is defaulted because we dont
		 care what it's name is*/
		if (error) {
			printf("ERROR %d in filled constraints GRBaddconstr(): %s\n", error,
					GRBgeterrormsg(env));
			free_stuffs(ind, val, vtype);
			return -1;
		}
	}
	/*
	 keeping for reference,this is from the example that was provided
	 First constraint: x + 2 y + 3 z <= 4

	 variables x,y,z (0,1,2)
	 ind[0] = 0;
	 ind[1] = 1;
	 ind[2] = 2;
	 coefficients (according to variables in "ind")
	 val[0] = 1;
	 val[1] = 2;
	 val[2] = 3;

	 add constraint to model - note size 3 + operator GRB_LESS_EQUAL
	 -- equation value (4.0) + unique constraint name
	 error = GRBaddconstr(model, 3, ind, val, GRB_LESS_EQUAL, 4.0, "c0");
	 if (error) {
	 printf("ERROR %d 1st GRBaddconstr(): %s\n", error,
	 GRBgeterrormsg(env));
	 free_stuffs(sol, ind, val, vtype);
	 return -1;
	 }

	 Second constraint: x + y >= 1
	 ind[0] = 0;
	 ind[1] = 1;
	 val[0] = 1;
	 val[1] = 1;

	 add constraint to model - note size 2 + operator GRB_GREATER_EQUAL
	 -- equation value (1.0) + unique constraint name
	 error = GRBaddconstr(model, 2, ind, val, GRB_GREATER_EQUAL, 1.0,
	 "c1");
	 if (error) {
	 printf("ERROR %d 2nd GRBaddconstr(): %s\n", error,
	 GRBgeterrormsg(env));
	 free_stuffs(sol, ind, val, vtype);
	 return -1;
	 }
	 Optimize model - need to call this before calculation
	 error = GRBoptimize(model);
	 if (error) {
	 printf("ERROR %d GRBoptimize(): %s\n", error,
	 GRBgeterrormsg(env));
	 free_stuffs(sol, ind, val, vtype);
	 return -1;
	 }
	 */

	/* Write model to 'mip1.lp' - this is not necessary but very helpful */
	error = GRBwrite(model, "mip1.lp");
	if (error) {
		printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/* Get solution information */

	error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
	if (error) {
		printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}
	/*probably dont need this since we maximize 0 in our shit my dude*/
	/* get the objective -- the optimal result of the function */
	error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
	if (error) {
		printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/* get the solution - the assignment to each variable */
	/* cols*rows*cols*rows*cols*rows-- number of variables, the size of "sol" should match */
	error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0,
			cols * rows * cols * rows * cols * rows, sol);
	if (error) {
		printf("ERROR %d GRBgetdblattrarray(): %s\n", error,
				GRBgeterrormsg(env));
		free_stuffs(ind, val, vtype);
		return -1;
	}

	/*TODO: Fill toBeFilled board with solution*/
	/*probably dont need these since we dont need to print to the user,maybe keep for the tests
	 print results
	 printf("\nOptimization complete\n");

	 solution found
	 if (optimstatus == GRB_OPTIMAL) {
	 printf("Optimal objective: %.4e\n", objval);
	 printf("  x=%.0f, y=%.0f, z=%.0f\n", sol[0], sol[1], sol[2]);
	 }
	 no solution found
	 else if (optimstatus == GRB_INF_OR_UNBD) {
	 printf("Model is infeasible or unbounded\n");
	 }
	 error or calculation stopped
	 else {
	 printf("Optimization was stopped early\n");
	 }
	 */

	/* IMPORTANT !!! - Free model and environment */
	GRBfreemodel(model);
	GRBfreeenv(env);
	free_stuffs(ind, val, vtype);
	if(optimstatus== GRB_INF_OR_UNBD)/*cant be unbound because the obj is const 0.if it's infesible then there is no solution,so return accordingly*/
		return 0;/*no solution*/
	return 1;/*found solution,and it's stored in sol*/
	}
