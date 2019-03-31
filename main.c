#include<stdio.h>
#include"globals.h"
#include"lexscan.h"
#include"util.h"

FILE *source;
FILE *outputfile;

int lineno=0;

int main(int argc){
	source=fopen("sample.tiny","r");
	outputfile=stdout;
	if(source==NULL){
		printf("Error opening file : SAMPLE.TINY\n");
		exit(1);
	}
	fprintf(outputfile,"\nTINY COMPILATION:\n");
	TokenType tt;
	do{
		tt=getToken();
		//printf("%d",tt);
	}while(tt!=EndFile);
	return 0;
}