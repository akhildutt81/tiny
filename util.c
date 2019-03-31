#include "globals.h"
#include "util.h"

void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case If:
    case Then:
    case Else:
    case End:
    case Repeat:
    case Until:
    case Read:
    case Write:
      fprintf(outputfile,"reserved word: %s\n",tokenString);
      break;
    case Assign: fprintf(outputfile,":=\n"); break;
    case Lt: fprintf(outputfile,"<\n"); break;
    case Eq: fprintf(outputfile,"=\n"); break;
    case Lparen: fprintf(outputfile,"(\n"); break;
    case Rparen: fprintf(outputfile,")\n"); break;
    case Semi: fprintf(outputfile,";\n"); break;
    case Plus: fprintf(outputfile,"+\n"); break;
    case Minus: fprintf(outputfile,"-\n"); break;
    case Times: fprintf(outputfile,"*\n"); break;
    case Over: fprintf(outputfile,"/\n"); break;
    case EndFile: fprintf(outputfile,"Eof\n"); break;
    case Num:
      fprintf(outputfile,"Num , val= %s\n",tokenString);
      break;
    case Id:
      fprintf(outputfile,"Id , name= %s\n",tokenString);
      break;
    case Error:
      fprintf(outputfile,"Error: %s\n",tokenString);
      break;
    default: /* should never happen */
      fprintf(outputfile,"Unknown token: %d\n",token);
  }
}