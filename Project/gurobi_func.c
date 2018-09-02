
#include <stdlib.h>
#include <stdio.h>

#include "gameStructs.h"
#include "MainAux.h"
#include "gurobi_c.h"

void free_stuffs(int* ind, double* val, double* obj, char* vtype) {
	free(ind);
	free(val);
	free(obj);
	free(vtype);
}

int addConstraints(int cols,int rows,int* ind,double* val,int* filled,int amountFilled,GRBenv *env,GRBmodel *model,double* obj,char* vtype){
	int i,j,k,l,a,error;
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
				free_stuffs(ind, val, obj, vtype);
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
				free_stuffs(ind, val, obj, vtype);
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
				free_stuffs(ind, val, obj, vtype);
				return -1;
			}
		}
	}
	/*same number only one per block*/
	for (i = 0; i < cols; i++) {/*block row index*/
		for (j = 0; j < rows; j++) {/*block col index*/
			for (k = 0; k < rows * cols; k++) {/*cell number index*/
				for (l = 0; l < rows; l++) {/*cell row index*/
					for (a = 0; a < cols; a++) {/*cell col index*/
						ind[l * cols + a] = (i * rows + l) * cols * rows * cols
								* rows + (j * cols + a) * cols * rows + k;
						val[l * cols + a] = 1;
					}
				}
				error = GRBaddconstr(model, cols * rows, ind, val, GRB_EQUAL,
						1.0, NULL);/*constraint name is defaulted because we dont
						 care what it's name is*/
				if (error) {
					printf("ERROR %d in block constraints GRBaddconstr(): %s\n",
							error, GRBgeterrormsg(env));
					free_stuffs(ind, val, obj, vtype);
					return -1;
				}
			}
		}
	}

	/*cells already filled constraints*/

	for (i = 0; i < amountFilled; i++) {/*data is in col row val triplets*/
		ind[0] = filled[i * 3] * cols * rows
				+ filled[(i * 3) + 1] * cols * rows * cols * rows
				+ filled[(i * 3) + 2] - 1;/*+0 is the col,+1 is the row,+2 is the value, we do -1 since indexing start from 0 and the value starts from 1*/
		val[0] = 1;
		error = GRBaddconstr(model, 1, ind, val, GRB_EQUAL, 1.0, NULL);/*constraint name is defaulted because we dont
		 care what it's name is*/
		if (error) {
			printf("ERROR %d in filled constraints GRBaddconstr(): %s\n", error,
					GRBgeterrormsg(env));
			free_stuffs(ind, val, obj, vtype);
			return -1;
		}
	}
	return 0;
}

int addVars(int cols,int rows,int* ind,double* val,double* obj,char* vtype,GRBenv *env,GRBmodel *model){
	int i,j,k,error;
	/* add variables and set the variables to be binary */
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
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}

	/* Change objective sense to maximization */
	error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
	if (error) {
		printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}

	/* update the model - to integrate new variables */

	error = GRBupdatemodel(model);
	if (error) {
		printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}
	return 0;
}

int findSol(int cols, int rows, int* filled, int amountFilled, double* sol) {/*return -1 on failure(error),0 on no solution,1 on solution found*/
	/*also need to return the solution of the filled board,so find how to optimally*/
	/*sol will hold which cells contain which numbers. We want to return the solution and to free it, so we allocate it outside and free it outside so we can return inside*/
	GRBenv *env = NULL;
	GRBmodel *model = NULL;
	int error = 0;
	int* ind;/*Which variable are used in each constraint*/
	double* val;/*The coefficients of the constraints*/
	double *obj = { 0 };
	char* vtype;/*What type the variable will be (all will be binary)*/
	int optimstatus;
	/*	double objval;*/
	ind = (int*) calloc(cols * rows, sizeof(int));
	checkInitalize(ind, "calloc");
	val = (double*) calloc(cols * rows, sizeof(double));
	checkInitalize(val, "calloc");
	vtype = (char*) calloc(cols * rows * cols * rows * cols * rows,
			sizeof(char));
	checkInitalize(vtype, "calloc");
	obj = (double*) calloc(cols * rows * cols * rows * cols * rows,
			sizeof(double));
	checkInitalize(obj, "calloc");
	/* Create environment - log file is mip1.log */
	error = GRBloadenv(&env, "mip1.log");
	if (error) {
		printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}

	/*Cancel log being written to console*/
	error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
	if (error) {
		printf("ERROR %d GRBsetintparam(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}

	/* Create an empty model named "mip1" */
	error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
	if (error) {
		printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}
	if(addVars(cols,rows,ind,val,obj,vtype,env,model)==-1)
		return -1;
	
	
	if(addConstraints(cols,rows,ind,val,filled,amountFilled,env,model,obj,vtype)==-1)
		return -1;

	/*  Optimize model - need to call this before calculation  */
	error = GRBoptimize(model);
	if (error) {
		printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}

	/* Write model to 'mip1.lp' - this is not necessary but very helpful */
	error = GRBwrite(model, "mip1.lp");
	if (error) {
		printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}

	/* Get solution information */

	error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
	if (error) {
		printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}
	if (optimstatus == GRB_INFEASIBLE) {
		GRBfreemodel(model);
		GRBfreeenv(env);
		free_stuffs(ind, val, obj, vtype);
		return 0;
	}
	/* get the solution - the assignment to each variable */
	error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0,
			cols * rows * cols * rows * cols * rows, sol);
	if (error) {
		printf("ERROR %d GRBgetdblattrarray(): %s\n", error,
				GRBgeterrormsg(env));
		free_stuffs(ind, val, obj, vtype);
		return -1;
	}

	

	/* Free model and environment */
	GRBfreemodel(model);
	GRBfreeenv(env);
	free_stuffs(ind, val, obj, vtype);
	return 1;/*found solution,and it's stored in sol*/
}
