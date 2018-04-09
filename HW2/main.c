#include "main_aux.h"
#include <stdio.h>
#include "SPBufferset.h"
#define const N getNumberOfHeaps() /*N=Number of heaps, the macro calls the function in the main_aux file*/

int main(){
	int heaps[N] = {0};
	SP_BUFF_SET();
	getHeapSizes(heaps);
	return 0;
}
