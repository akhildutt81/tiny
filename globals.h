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

extern int scannerOutput;

typedef enum{
	EndFile,Error,
	If,Then,Else,End,Repeat,Until,Read,Write,
	Id,Num,
	Assign,Eq,Lt,Plus,Minus,Times,Over,Lparen,Rparen,Semi
}TokenType;

extern int lineno;

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;
extern int Err;
#endif