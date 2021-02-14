hash:  symtablehash.o testsymtab.c symtable.h
	gcc  -ansi -pedantic -Wall symtablehash.o testsymtab.c symtable.h -o hash
	
list:  symtablelist.o testsymtab.c symtable.h
	gcc  -ansi -pedantic -Wall symtablelist.o testsymtab.c symtable.h -o list

symtablelist.o:	symtablelist.c symtable.h
	gcc  -ansi -pedantic -Wall -c symtablelist.c
symtablehash.o:	symtablehash.c	 symtable.h
	gcc -ansi -pedantic -Wall -c symtablehash.c

clean:
	rm -f *.o *~  
	rm -f *.o hash list

