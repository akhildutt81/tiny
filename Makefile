output: main.o util.o lex.yy.o -ll
	gcc main.o util.o lex.yy.o -o output -ll
main.o: main.c globals.h
	gcc -c main.c
util.o: util.c util.h
	gcc -c util.c
lex.yy.o: lex.yy.c lexscan.h
	gcc -c lex.yy.c