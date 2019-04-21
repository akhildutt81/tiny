output: main.o util.o lex.yy.o parse.0
	gcc main.o util.o lex.yy.o parse.o -o output -ll
main.o: main.c globals.h
	gcc -c main.c
util.o: util.c util.h
	gcc -c util.c
lex.yy.o: lex.yy.c lexscan.h
	gcc -c lex.yy.c
parse.0: parse.c parse.h
	gcc -c parse.c