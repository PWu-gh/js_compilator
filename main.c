/* file TP.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
#include "parseur.tab.h"/* header for TOKEN */
#include "AST.c"	/* AST fonctions */

int main(void)
{
  AST t; 				/* &t allows to modifie the tree */
  if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
    printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
    
    /* print the obtained tree */
    if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);	/* check if car at root */
    printAST(t); printf("\n");
    		
    freeAST(t);
  } 
  exit(EXIT_SUCCESS);
}

