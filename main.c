/* file TP.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
#include "parseur.tab.h"/* header for TOKEN */
#include "AST.c"	/* AST fonctions */
#include <string.h>

extern  int yyparse (void*);
extern int yy_scan_string(const char *);

int main(int argc, char* argv[])
{
    AST t; 				/* &t allows to modifie the tree */
    if(argc > 1){

        FILE * inputFile = freopen( argv[1], "r", stdin); // redirect entry val to file content

        
        if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
			printf("Parsing:: syntax OK\n");/* reached if parsing folllows the grammar */
			
			/* print the obtained tree */
            printf("\n_______________________\n");
			if (t->left!=NULL) printf("Root symbol:: %s\n", t->car);	/* check if car at root */

            processCast(t);
			printAST(t); 
            retCountJump(t);

            printf("\n\n");

            // generate assembly code in Fname.jsm
            char* Fname = strcat(strtok(argv[1],"."),".jsm");
            remove(Fname);
            FILE* jsm_file = freopen(Fname,"a+", stdout);
            genAssembly(t);
            fclose(jsm_file);
			freeAST(t);
        } 
        fclose(inputFile);
    }
    else{
        printf("\nExpression : ");
        char str[100];
        scanf("%[^\n]", str); //prend toute la ligne
        yy_scan_string(str);

        if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
			printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
			

            /* print Assembly code of the obtained tree */
            printf("\n\n_______________________\n");
            printf("Assembly : \n\n");

            retCountJump(t);
            genAssembly(t); // gen dans terminal

            /* print the obtained tree */
            printf("\n_______________________\n");
            printf("AST : \n\n");
			if (t->left!=NULL) printf("Root symbol : %s\n", t->car);	/* check if car at root */
			printAST(t); 
            
            printf("\n\n");
            	
			freeAST(t);
        } 
    }


    exit(EXIT_SUCCESS);
}

