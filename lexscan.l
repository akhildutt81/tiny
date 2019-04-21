%{
  #include "globals.h"
  #include "util.h"
  #include "lexscan.h"
  char tokenString[40];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+
cnewline    \r\n

%%

"if"            return If;
"then"          return Then;
"else"          return Else;
"end"           return End;
"repeat"        return Repeat;
"until"         return Until;
"read"          return Read;
"write"         return Write;
":="            return Assign;
"="             return Eq;
"<"             return Lt;
"+"             return Plus;
"-"             return Minus;
"*"             return Times;
"/"             return Over;
"("             return Lparen;
")"             return Rparen;
";"             return Semi;
{number}        return Num;
{identifier}    return Id;
{cnewline}      lineno++;
{newline}       lineno++;
{whitespace}    ;
"{"             { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (c != '}');
                }
.               return Error;

%%

TokenType getToken(void){ 
  static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { 
    firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = outputfile;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,40);
  if(scannerOutput){
    fprintf(outputfile,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

