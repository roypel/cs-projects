COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors
OBJS = main.o MainAux.o parser.o solver.o game.o fileFunc.o linkedListFunc.o stackFunc.o

sudoku: $(OBJS)
	gcc -o $@ $(OBJS)

main.o: main.c parser.h MainAux.h gameStructs.h SPBufferset.h
	gcc $(COMP_FLAG) -c $*.c

MainAux.o: MainAux.c MainAux.h gameStructs.h
	gcc $(COMP_FLAG) -c $*.c

parser.o: parser.c parser.h game.h gameStructs.h MainAux.h fileFunc.h solver.h
	gcc $(COMP_FLAG) -c $*.c

game.o: game.c game.h parser.h MainAux.h solver.h gameStructs.h linkedListFunc.h
	gcc $(COMP_FLAG) -c $*.c

solver.o: solver.c solver.h game.h gameStructs.h linkedListFunc.h stackFunc.h MainAux.h
	gcc $(COMP_FLAG) -c $*.c

fileFunc.o: fileFunc.c fileFunc.h gameStructs.h linkedListFunc.h solver.h game.h
	gcc $(COMP_FLAG) -c $*.c


linkedListFunc.o: linkedListFunc.c linkedListFunc.h gameStructs.h
	gcc $(COMP_FLAG) -c $*.c


stackFunc.o: stackFunc.c stackFunc.h gameStructs.h
	gcc $(COMP_FLAG) -c $*.c

clean:
	rm -f $(OBJS)
