/* Copyright 2018, I-Lakunishok-Peleg, Inc. */

/* This example formulates and solves the following simple MIP model:

 maximize    x +   y + 2 z
 subject to  x + 2 y + 3 z <= 4
 x +   y       >= 1
 x, y, z binary
 */

#include <stdlib.h>
#include <stdio.h>
#include "gurobi_c.h"

void free_stuffs(){
	free(sol);
	free(ind);
	free(val);
	free(vtype);
}
/*check if filled can be int** and not just int* since this is gurobi*/
int fillboard(int cols, int rows, int** filled) {/*return -1 on failure,1/integer on success*/
	/*also need to return the solution of the filled board,so find howto optimally*/
	int i,j,k;
	GRBenv *env = NULL;
	GRBmodel *model = NULL;
	int error = 0;
	int* sol;
	int* ind;
	int* val;
	int obj[1]={0};
	char* vtype;
	int optimstatus;
	double objval;

	sol=(int*)calloc(cols*rows*cols*rows*cols*rows,sizeof(int));
	ind=(int*)calloc(cols*rows,sizeof(int));
	val=(int*)calloc(cols*rows,sizeof(int));
	vtype=(char*) calloc(cols*rows*cols*rows*cols*rows);

	/* Create environment - log file is mip1.log */
	error = GRBloadenv(&env, "mip1.log");
	if (error) {
		printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}
	/*Cancel log being written to console*/
	error=GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0)
	if(error){
		printf("ERROR %d GRBsetintparam(): %s\n",error,GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* Create an empty model named "mip1" */
	error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL );
	if (error) {
		printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* Add variables */


	/* set the variables to be binary */
	for(i=0;i<cols*rows;i++){
		for(j=0;j<cols*rows;j++){
			for(k=0;k<cols*rows;k++){
				vtype[i*cols*rows*cols*rows+j*cols*rows+k]=GRB_BINARY;
			}
		}
	}

	/* add variables to model */
	error = GRBaddvars(model, cols*rows*cols*rows*cols*rows, 0, NULL, NULL, NULL, obj, NULL, NULL, vtype,
			NULL );
	if (error) {
		printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* Change objective sense to maximization */
	error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
	if (error) {
		printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* update the model - to integrate new variables */

	error = GRBupdatemodel(model);
	if (error) {
		printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}
	
	/*only one number per cell constraints*/
	for(i=0;i<cols*rows;i++){
		for(j=0;j<cols*rows;j++){
			for(k=0;k<cols*rows;k++){
				ind[k]=i*cols*rows*cols*rows+j*cols*rows+k;
				val[k]=1;
			}
			error = GRBaddconstr(model, cols*rows, ind, val, GRB_EQUAL, 1.0, NULL);/*constraint name is defaulted because we dont
												care what it's name is*/
			if (error) {
				printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
				free_stuffs();
				return -1;
			}
		}
	}
	/*same number only once per row constraints*/
	for(i=0;i<cols*rows;i++){
		for(k=0;k<cols*rows;k++){
			for(j=0;j<cols*rows;j++){
				ind[j]=i*cols*rows*cols*rows+j*cols*rows+k;
				val[j]=1;
			}
			error = GRBaddconstr(model, cols*rows, ind, val, GRB_EQUAL, 1.0, NULL);/*constraint name is defaulted because we dont
												care what it's name is*/
			if (error) {
				printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
				free_stuffs();
				return -1;
		}
	}
	
	/*same number only once per col constraints*/
	for(j=0;j<cols*rows;j++){
		for(k=0;k<cols*rows;k++){
			for(i=0;i<cols*rows;i++){
				ind[i]=i*cols*rows*cols*rows+j*cols*rows+k;
				val[i]=1;
			}
			error = GRBaddconstr(model, cols*rows, ind, val, GRB_EQUAL, 1.0, NULL);/*constraint name is defaulted because we dont
												care what it's name is*/
			if (error) {
				printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
				free_stuffs();
				return -1;
		}
	}
	
	/*same number only once per block constraints*/

	/*cells already filled constraints*/
	/*check if filled can be int** and not just int* since this is gurobi*/
	for(i=0;i<(int)( sizeof(filled) / sizeof(filled[0])),i++){
		ind[0]=filled[i][0]*cols*rows+filled[i][1]*cols*rows*cols*rows+filled[i][2];/*[0] is the col,[1] is the row,[k] is the value*/
		val[0]=1;
		error = GRBaddconstr(model, 1, ind, val, GRB_EQUAL, 1.0, NULL);/*constraint name is defaulted because we dont
												care what it's name is*/
		if (error) {
			printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
			free_stuffs();
			return -1;
		}
	}

	/* First constraint: x + 2 y + 3 z <= 4 */

	/* variables x,y,z (0,1,2) */
	ind[0] = 0;
	ind[1] = 1;
	ind[2] = 2;
	/* coefficients (according to variables in "ind") */
	val[0] = 1;
	val[1] = 2;
	val[2] = 3;

	/* add constraint to model - note size 3 + operator GRB_LESS_EQUAL */
	/* -- equation value (4.0) + unique constraint name */
	error = GRBaddconstr(model, 3, ind, val, GRB_LESS_EQUAL, 4.0, "c0");
	if (error) {
		printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* Second constraint: x + y >= 1 */
	ind[0] = 0;
	ind[1] = 1;
	val[0] = 1;
	val[1] = 1;

	/* add constraint to model - note size 2 + operator GRB_GREATER_EQUAL */
	/* -- equation value (1.0) + unique constraint name */
	error = GRBaddconstr(model, 2, ind, val, GRB_GREATER_EQUAL, 1.0, "c1");
	if (error) {
		printf("ERROR %d 2nd GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* Optimize model - need to call this before calculation */
	error = GRBoptimize(model);
	if (error) {
		printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* Write model to 'mip1.lp' - this is not necessary but very helpful */
	error = GRBwrite(model, "mip1.lp");
	if (error) {
		printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* Get solution information */

	error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
	if (error) {
		printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* get the objective -- the optimal result of the function */
	error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
	if (error) {
		printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* get the solution - the assignment to each variable */
	/* 3-- number of variables, the size of "sol" should match */
	error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, 3, sol);
	if (error) {
		printf("ERROR %d GRBgetdblattrarray(): %s\n", error,
				GRBgeterrormsg(env));
		free_stuffs();
		return -1;
	}

	/* print results */
	printf("\nOptimization complete\n");

	/* solution found */
	if (optimstatus == GRB_OPTIMAL) {
		printf("Optimal objective: %.4e\n", objval);
		printf("  x=%.0f, y=%.0f, z=%.0f\n", sol[0], sol[1], sol[2]);
	}
	/* no solution found */
	else if (optimstatus == GRB_INF_OR_UNBD) {
		printf("Model is infeasible or unbounded\n");
	}
	/* error or calculation stopped */
	else {
		printf("Optimization was stopped early\n");
	}

	/* IMPORTANT !!! - Free model and environment */
	GRBfreemodel(model);
	GRBfreeenv(env);
	free_stuffs();
	return 0;
}
