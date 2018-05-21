COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors
OBJS = main.o MainAux.o parser.o solver.o game.o

sudoku: $(OBJS)
	gcc -o $@ $(OBJS)

main.o: main.c parser.h MainAux.h gameStructs.h SPBufferset.h
	gcc $(COMP_FLAG) -c $*.c

MainAux.o:MainAux.c MainAux.h gameStructs.h
	gcc $(COMP_FLAG) -c $*.c

parser.o:parser.c parser.h game.h gameStructs.h
	gcc $(COMP_FLAG) -c $*.c

game.o:parser.c parser.h MainAux.h solver.h gameStructs.h
	gcc $(COMP_FLAG) -c $*.c

solver.o:solver.c solver.h game.h gameStructs.h
	gcc $(COMP_FLAG) -c $*.c

clean:
	rm -f $(OBJS)