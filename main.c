/* file main.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */
//#include "parseur.tab.h"

int main(int argc, char* argv[])
{

    if(argc > 1){
        FILE * outputFile;
        outputFile = freopen( argv[1], "r", stdin); // redirect stdout dans le fichier
        
        if (yyparse()==0) { /* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n"); /* reached if parsing follows the grammar */

        }
        fclose(outputFile);
    }
    else{
        printf("\nParsing:: syntax OK\n"); 
        if (yyparse()==0) { /* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n"); 
        }
    }


    exit(EXIT_SUCCESS);
}
