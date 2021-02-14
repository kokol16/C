sudoku:  sudoku.o grid.o sudoku.h grid.h
	gcc  -ansi -pedantic -Wall sudoku.o sudoku.h grid.o grid.h -o sudoku
	

sudoku.o:	sudoku.c sudoku.h
	gcc  -ansi -pedantic -Wall -c sudoku.c

gird.o:	gird.c grid.h
	gcc  -ansi -pedantic -Wall -c sudoku.c

clean:
	rm -f *.o *~  
	rm -f *.o sudoku

