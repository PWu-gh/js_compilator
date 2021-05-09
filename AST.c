#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(double val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

/* delete an AST */
void freeAST(AST t)
{
  if (t!=NULL) {
    freeAST(t->left);
    freeAST(t->right);
    free(t);
  }
}

/* infix print an AST*/
void printAST(AST t)
{
  if (t!=NULL) {
    printf("[ ");
    printAST(t->left);
    /* check if node is car|val */
    if (t->left==NULL) printf("%f ",t->val); 
    else printf("%c ",t->car);
    printAST(t->right);
    printf("] ");
  }
}

void newPrintAST(AST t)
{
	if (t!=NULL) {
		printf(" [");
		newPrintAST(t->left);
		if (t->left==NULL) printf("CsteNb %f",t->val); 
		else {

			switch (t->car)
			{
			case '+':
				printf("AddiNb");
				break;
			case '*':
				printf("MultNb");
				break;
			case '-':
				if(t->right == NULL) printf("NegaNb ");
				else printf("SubiNb");
				break;
			case '/':
				printf("DiviNb");
				break;

      // bool
      case 'E': // ""
				printf("Equals");
				break;
      case '!': // !
				printf("Not");
				break;
      case 'N': //!=
				printf("NotEql");
				break;
			case '<': // <
				printf("LoStNb");
				break;
      case 'L': // <=
				printf("LoEqNb");
				break;
      case '>': // >
				printf("GrStNb");
				break;
      case 'G': // >=
				printf("GrEqNb");
				break;

			default:
				// symbole non implemente
				printf("%c ",t->car);
				break;
			}
		}
		newPrintAST(t->right);

		printf("] ");
	}
}

void compute(AST t){
  
}
