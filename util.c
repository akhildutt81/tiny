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

TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(outputfile,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(outputfile,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(outputfile,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(outputfile," ");
}

/* procedure printTree prints a syntax tree to the 
 * outputfile file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(outputfile,"If\n");
          break;
        case RepeatK:
          fprintf(outputfile,"Repeat\n");
          break;
        case AssignK:
          fprintf(outputfile,"Assign to: %s\n",tree->attr.name);
          break;
        case ReadK:
          fprintf(outputfile,"Read: %s\n",tree->attr.name);
          break;
        case WriteK:
          fprintf(outputfile,"Write\n");
          break;
        default:
          fprintf(outputfile,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(outputfile,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(outputfile,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(outputfile,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(outputfile,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(outputfile,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
