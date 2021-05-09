/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */
%{
    #include <stdio.h> /* printf */
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
expression PT_VIRG { printf("Resultat= %d\n", $1); }
|expression PT_VIRG resultat { printf("Resultat= %d\n", $1); }
;



expression:
    expression '+' expression       { $$ = $1+$3; }
    | expression '-' expression     { $$ = $1-$3; }
    | expression '*' expression     { $$ = $1*$3; }
    | expression '/' expression     { $$ = $1/$3; }
    | '(' expression ')'            { $$ = $2; }
    | '-' expression %prec MOINSU   { $$ = -$2; }
    | NOMBRE                        { $$ = $1; }
    | bool_op
;

bool_op:
    BOOLEAN
    | expression EQ expression  { $$ = $1 == $3; printf("\n %d", $$)}
    | expression SUPEQ expression

;


%%

int yyerror(const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */