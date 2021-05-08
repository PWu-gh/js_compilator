/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

/* comlements: https://www.gnu.org/software/bison/manual/html_node/Parser-Function.html */
/* about implicit call: https://stackoverflow.com/questions/20106574/simple-yacc-grammars-give-an-error */

%{
 #include <stdio.h>	/* printf REMOVE AFTER TEST */
 #include "AST.h"
 int yylex(void);	/* flex with -Wall (implicite call) */
 int yyerror(struct _tree**, const char*); /* same for bison */
%}



%union {
  struct _tree* exp;
  double doubleVal;
};

%parse-param {struct _tree* *pT} // yyparse(&t) call => *pT = *(&t) = t 


%type  <exp> expression
%token <doubleVal> NOMBRE
%token PT_VIRG

%left '+' '-'
%left '*' '/'
%nonassoc MOINSU



%%

resultat: 
  expression PT_VIRG  { *pT = $1; }
  |expression PT_VIRG resultat { *pT = $1; }
;


expression: 
    expression '+' expression	{ $$ = newBinaryAST('+',$1,$3); }
  | expression '-' expression	{ $$ = newBinaryAST('-',$1,$3); }
  | expression '*' expression	{ $$ = newBinaryAST('*',$1,$3); }
  | expression '/' expression	{ $$ = newBinaryAST('/',$1,$3); }
  | '(' expression ')'		{ $$ = $2; }
  | '-' expression %prec MOINSU	{ $$ = newUnaryAST('-',$2); }
  | NOMBRE			{ $$ = newLeafAST($1); } 
  ;




%%

#include <stdio.h>	/* printf */
int yyerror(struct _tree **pT, const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */

