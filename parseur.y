/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */
%{
    int yylex(void); /* -Wall : avoid implicit call */
    int yyerror(const char*); /* same for bison */
%}


%token NOMBRE PT_VIRG 
%token BOOLEAN EQ SUPEQ

%left '+' '-'
%left '*' '/'
%nonassoc MOINSU


%%

resultat: 
expression PT_VIRG
|expression PT_VIRG resultat
;



expression:
expression '+' expression
| expression '-' expression
| expression '*' expression
| expression '/' expression
| '(' expression ')'
| '-' expression %prec MOINSU
| NOMBRE
| bool_op
;

bool_op:
    BOOLEAN
    | expression EQ expression
    | expression SUPEQ expression

;


%%

#include <stdio.h> /* printf */
int yyerror(const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */