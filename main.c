#include<stdio.h>
#include"globals.h"
#include"lexscan.h"
#include"util.h"
#include"parse.h"

FILE *source;
FILE *outputfile;

int scannerOutput=FALSE;
static int parserOutput=FALSE;
int lineno=0;

int Err=TRUE;

int main(int argc,char* argv){
	TreeNode *tree;
	source=fopen("sample2.tiny","r");
	int opt;
	scanf("%d",&opt);
	outputfile=stdout;
	if(source==NULL){
		printf("Error opening file : SAMPLE.TINY\n");
		exit(1);
	}
	fprintf(outputfile,"\nTINY COMPILATION:\n");
	TokenType tt;
	if(opt==0){
		scannerOutput=TRUE;
	}
	else if(opt==1){
		parserOutput=TRUE;
	}
	tree=parse();
	if(parserOutput){
		printTree(tree);		
	}
	return 0;
}
