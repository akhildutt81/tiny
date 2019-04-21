#include "globals.h"
#include "util.h"
#include "lexscan.h"
#include "parse.h"

static TokenType token; /* holds current token */

static TreeNode * stmt_sequence(void);
static TreeNode * statement(void);
static TreeNode * if_stmt(void);
static TreeNode * repeat_stmt(void);
static TreeNode * assign_stmt(void);
static TreeNode * read_stmt(void);
static TreeNode * write_stmt(void);
static TreeNode * exp(void);
static TreeNode * simple_exp(void);
static TreeNode * term(void);
static TreeNode * factor(void);

static void syntaxError(char * message)
{ fprintf(outputfile,"\n>>> ");
  fprintf(outputfile,"Syntax error at line %d: %s",lineno,message);
  Err = TRUE;
}

static void match(TokenType expected)
{ if (token == expected) token = getToken();
  else {
    syntaxError("unexpected token -> ");
    printToken(token,tokenString);
    syntaxError("expected toke -> ");
    printToken(expected,tokenString);
    fprintf(outputfile,"      ");
  }
}

TreeNode * stmt_sequence(void)
{ TreeNode * t = statement();
  TreeNode * p = t;
  while ((token!=EndFile) && (token!=End) &&
         (token!=Else) && (token!=Until))
  { TreeNode * q;
    match(Semi);
    q = statement();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else /* now p cannot be NULL either */
      { p->sibling = q;
        p = q;
      }
    }
  }
  return t;
}

TreeNode * statement(void)
{ TreeNode * t = NULL;
  switch (token) {
    case If : t = if_stmt(); break;
    case Repeat : t = repeat_stmt(); break;
    case Id : t = assign_stmt(); break;
    case Read : t = read_stmt(); break;
    case Write : t = write_stmt(); break;
    default : syntaxError("unexpected token -> ");
              printToken(token,tokenString);
              token = getToken();
              break;
  } /* End case */
  return t;
}

TreeNode * if_stmt(void)
{ TreeNode * t = newStmtNode(IfK);
  match(If);
  if (t!=NULL) t->child[0] = exp();
  match(Then);
  if (t!=NULL) t->child[1] = stmt_sequence();
  //printf("/n****** %d \n",token);
  if (token==Else) {
    match(Else);
    if (t!=NULL) t->child[2] = stmt_sequence();
  }
  match(End);
  return t;
}

TreeNode * repeat_stmt(void)
{ TreeNode * t = newStmtNode(RepeatK);
  match(Repeat);
  if (t!=NULL) t->child[0] = stmt_sequence();
  match(Until);
  if (t!=NULL) t->child[1] = exp();
  return t;
}

TreeNode * assign_stmt(void)
{ TreeNode * t = newStmtNode(AssignK);
  if ((t!=NULL) && (token==Id))
    t->attr.name = copyString(tokenString);
  match(Id);
  match(Assign);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * read_stmt(void)
{ TreeNode * t = newStmtNode(ReadK);
  match(Read);
  if ((t!=NULL) && (token==Id))
    t->attr.name = copyString(tokenString);
  match(Id);
  return t;
}

TreeNode * write_stmt(void)
{ TreeNode * t = newStmtNode(WriteK);
  match(Write);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * exp(void)
{ TreeNode * t = simple_exp();
  if ((token==Lt)||(token==Eq)) {
    TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
    }
    match(token);
    if (t!=NULL)
      t->child[1] = simple_exp();
  }
  return t;
}

TreeNode * simple_exp(void)
{ TreeNode * t = term();
  while ((token==Plus)||(token==Minus))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = term();
    }
  }
  return t;
}

TreeNode * term(void)
{ TreeNode * t = factor();
  while ((token==Times)||(token==Over))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = factor();
    }
  }
  return t;
}

TreeNode * factor(void)
{ TreeNode * t = NULL;
  switch (token) {
    case Num :
      t = newExpNode(ConstK);
      if ((t!=NULL) && (token==Num))
        t->attr.val = atoi(tokenString);
      match(Num);
      break;
    case Id :
      t = newExpNode(IdK);
      if ((t!=NULL) && (token==Id))
        t->attr.name = copyString(tokenString);
      match(Id);
      break;
    case Lparen :
      match(Lparen);
      t = exp();
      match(Rparen);
      break;
    default:
      syntaxError("unexpected token -> ");
      printToken(token,tokenString);
      token = getToken();
      break;
    }
  return t;
}

TreeNode * parse(void)
{ TreeNode * t;
  token = getToken();
  t = stmt_sequence();
  if (token!=EndFile)
    syntaxError("Code Ends before file\n");
  return t;
}
