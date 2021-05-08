/* file TP.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
#include "parseur.tab.h"/* header for TOKEN */
#include "AST.c"	/* AST fonctions */
#include <string.h>


int main(int argc, char* argv[])
{

    if(argc > 1){
        FILE * inputFile;
        FILE * jsmFile;
        inputFile = freopen( argv[1], "r", stdin); // redirect stdout dans le fichier

        // creer le fichier .jsm
        char * rename = strncpy(rename, argv[1], strlen(argv[1])-3);
        rename[strlen(rename)-3] = '\0'; // strncpy ne reduit pas le buffer
        strcat(rename, "jsm");
        jsmFile = fopen(rename, "w+");
        fclose(jsmFile);

        
        AST t; 				/* &t allows to modifie the tree */
        if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
			printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
			
			/* print the obtained tree */
			if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);	/* check if car at root */
			printAST(t); 
            printf("\n\n");
            newPrintAST(t); 
				
			freeAST(t);
        } 
        fclose(inputFile);
    }
    else{
        AST t; 				/* &t allows to modifie the tree */
        if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
			printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
			
			/* print the obtained tree */
			if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);	/* check if car at root */
			printAST(t); 
            printf("\n");
				
			freeAST(t);
        } 
    }


    exit(EXIT_SUCCESS);
}

