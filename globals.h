#ifndef _globals_h_
#define _globals_h_

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

extern FILE *outputfile;
extern FILE *source;

extern int lineno;

typedef enum{
	EndFile,Error,
	If,Then,Else,End,Repeat,Until,Read,Write,
	Id,Num,
	Assign,Eq,Lt,Plus,Minus,Times,Over,Lparen,Rparen,Semi
}TokenType;

extern int lineno;

#endif