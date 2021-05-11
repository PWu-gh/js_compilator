#ifndef _AST_H_
#define _AST_H_
/* unary-and-binary tree structure */
struct _tree {
  char* car;              /* char* for arithmetic operation */
  double val;			        /* double  for value */
  char* boo;
  struct _tree* left;    	/* used for unary node but NULL if leaf */
  struct _tree* right;   	/* NULL if unary node or leaf*/
};

typedef struct _tree* AST;

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char* car, AST left, AST right);

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son);

/* create an AST leaf from a value */
AST newLeafAST(double val);
AST newLeafBool(char* bool_str);

/* delete an AST */
void freeAST(AST t);

/* print an AST*/
void printAST(AST t);

#endif // !_AST_H_
