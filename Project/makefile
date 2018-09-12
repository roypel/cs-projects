COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
OBJS = main.o mainAux.o parser.o solver.o game.o fileFunc.o linkedListFunc.o stackFunc.o gurobiFunc.o
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

all: sudoku-console

sudoku-console: $(OBJS)
	gcc -o $@ $(OBJS) $(GUROBI_LIB)

main.o: main.c parser.h mainAux.h gameStructs.h SPBufferset.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

mainAux.o: mainAux.c mainAux.h gameStructs.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

parser.o: parser.c parser.h game.h gameStructs.h mainAux.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

game.o: game.c game.h mainAux.h solver.h gameStructs.h linkedListFunc.h gurobiFunc.h fileFunc.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

solver.o: solver.c solver.h gameStructs.h linkedListFunc.h stackFunc.h mainAux.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

fileFunc.o: fileFunc.c fileFunc.h gameStructs.h linkedListFunc.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

linkedListFunc.o: linkedListFunc.c linkedListFunc.h gameStructs.h mainAux.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

stackFunc.o: stackFunc.c stackFunc.h gameStructs.h mainAux.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

gurobiFunc.o: gurobiFunc.c gurobiFunc.h gameStructs.h mainAux.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

clean:
	rm -f $(OBJS)