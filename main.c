/* file main.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */
//#include "parseur.tab.h"
#include <stdbool.h>

int main(int argc, char* argv[])
{
    bool test = (5*5) == true;
    printf("%d", test);

    if(argc > 1){
        FILE * inputFile;
        inputFile = freopen( argv[1], "r", stdin); // redirect stdout dans le fichier
        
        if (yyparse()==0) { /* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n"); /* reached if parsing follows the grammar */

        }
        fclose(inputFile);
    }
    else{
        printf("\nParsing:: syntax OK\n"); 
        if (yyparse()==0) { /* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n"); 
        }
    }


    exit(EXIT_SUCCESS);
}
