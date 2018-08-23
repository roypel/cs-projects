COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
OBJS = main.o MainAux.o parser.o solver.o game.o fileFunc.o linkedListFunc.o stackFunc.o gurobi_func.o
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

all: sudoku-console $(OBJS)
	gcc -o $@ $(OBJS) $(GUROBI_LIB)

main.o: main.c parser.h MainAux.h gameStructs.h SPBufferset.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

MainAux.o: MainAux.c MainAux.h gameStructs.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

parser.o: parser.c parser.h game.h gameStructs.h MainAux.h fileFunc.h solver.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

game.o: game.c game.h parser.h MainAux.h solver.h gameStructs.h linkedListFunc.h gurobi_func.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

solver.o: solver.c solver.h game.h gameStructs.h linkedListFunc.h stackFunc.h MainAux.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

fileFunc.o: fileFunc.c fileFunc.h gameStructs.h linkedListFunc.h solver.h game.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c


linkedListFunc.o: linkedListFunc.c linkedListFunc.h gameStructs.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

stackFunc.o: stackFunc.c stackFunc.h gameStructs.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

gurobi_func.o: gurobi_func.c gurobi_func.h gameStructs.h
	gcc $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

clean:
	rm -f $(OBJS)
