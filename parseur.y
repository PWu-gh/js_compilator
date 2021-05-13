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
    char * str;
};

%parse-param {struct _tree* *pT} // yyparse(&t) call => *pT = *(&t) = t 


%type  <exp> resultat command expression Bool_exp 
%token <doubleVal> NOMBRE 
%token PT_VIRG 
%token <str> BOOLEAN 
%token Equals NotEql LoStNb LoEqNb GrStNb GrEqNb
%token <str> VAR
%token <str> PLUS1
%token <str> IF ELSE DO WHILE
%token <str> OR AND

%right '='
%left Equals NotEql LoStNb LoEqNb GrStNb GrEqNb
%left '+' '-'
%left '*' '/'
%left Not PLUS1 
%left OR AND




%nonassoc MOINSU



%%

resultat: 
    command { *pT = $1; }
    | command resultat { *pT = newBinaryAST(";", $1, $2); }
;

command:
    expression PT_VIRG      { $$ = $1;}
    | ';'                   {;}
    | '{' command '}'       { $$ = $2; } 
    | IF expression command ELSE command  { $$ =  newBinaryAST(
                                                    "ITE",
                                                    newUnaryAST("ConJump",$2) ,
                                                    newBinaryAST("TF", 
                                                                newUnaryAST("jumpElse", $3), 
                                                                $5 ) );}
    // | IF expression command ELSE command    { $$ =  newBinaryAST("ConJump",$2, newBinaryAST("skipElse",$3,$5));}
;

expression: 
    expression '+' expression	{ $$ = newBinaryAST("+",$1,$3); }
    | expression '-' expression	{ $$ = newBinaryAST("-",$1,$3); }
    | expression '*' expression	{ $$ = newBinaryAST("*",$1,$3); }
    | expression '/' expression	{ $$ = newBinaryAST("/",$1,$3); }
    | '(' expression ')'		{ $$ = $2; }
    | '-' expression %prec MOINSU	{ $$ = newUnaryAST("-",$2); }
    | NOMBRE			{ $$ = newLeafAST($1);} 
    | Bool_exp
    | VAR                         { $$ = newLeafVar($1);}
    | expression '=' expression    { $$ = newBinaryAST("=",$3, newUnaryAST($1->var, newLeafCar("bait"))); }
    | expression PLUS1     { $$ = newUnaryAST("++",$1); }
;

Bool_exp:
    BOOLEAN                         { $$ = newLeafBool($1);} 
    | expression Equals expression  { $$ = newBinaryAST("==",$1,$3);}
    | Not expression %prec MOINSU   { $$ = newUnaryAST("!",$2);}
    | expression NotEql expression  { $$ = newBinaryAST("!=",$1,$3); }
    | expression LoStNb expression  { $$ = newBinaryAST("<",$1,$3); }
    | expression LoEqNb expression  { $$ = newBinaryAST("<=",$1,$3); }
    | expression GrStNb expression  { $$ = newBinaryAST(">",$1,$3); }
    | expression GrEqNb expression  { $$ = newBinaryAST(">=",$1,$3); }
    | Bool_exp AND Bool_exp  { $$ = newBinaryAST("&&",$1,$3); }
    | Bool_exp OR Bool_exp  { $$ = newBinaryAST("||",$1,$3); }
;

// Var_exp:
//     VAR                         { $$ = newLeafVar($1);}
//     | Var_exp '=' expression    { $$ = newBinaryAST("=",$3,$1);}
//     | Var_exp PLUS1     { $$ = newUnaryAST("++",newLeafVar($1)); }
// ;


%%

int yyerror(struct _tree **pT, const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */

