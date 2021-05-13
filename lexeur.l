/* file lexeur.l */ 
/* compilation: flex lexeur.l */
/* result: lex.yy.c = lexical analyser in C */

%{
 #include <stdio.h>       /* printf */
 #include "parseur.tab.h" /* token constants def. in parseur.y via #define */
%}

%x COMMENT

%%

[0-9]+(\.[0-9]+)?(e-?[0-9]+)? { printf("lex::NOMBRE %s\n",yytext); yylval.doubleVal=atof(yytext);  return NOMBRE; }

"True"|"False" { printf("lex::BOOLEAN %s\n",yytext); yylval.str=yytext; return BOOLEAN; }
"=="    { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return Equals; }
"!"     { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return Not; }
"!="    { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return NotEql; }
"<"     { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return LoStNb; }
"<="    { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return LoEqNb; }
">"     { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return GrStNb; }
">="    { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return GrEqNb; }

[a-z][a-zA-Z0-9_]* { printf("lex::VAR %s\n",yytext); yylval.str=yytext; return VAR; }
"++"        { printf("lex::OP %s\n",yytext); yylval.str=yytext; return PLUS1; }
"NaN" { printf("lex::NOMBRE %s\n",yytext); yylval.doubleVal= -9;  return NOMBRE; }

"If"    { printf("lex::COND \n"); yylval.str=yytext; return IF; }
"Else"  { printf("lex::COND \n"); yylval.str=yytext; return ELSE; }

"||"     { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return OR; }
"&&"    { printf("lex::BOOL_OP %s\n",yytext); yylval.str=yytext; return AND; }

"Do"    { printf("lex::DO \n"); yylval.str=yytext; return DO; }
"While" { printf("lex::COND \n"); yylval.str=yytext; return WHILE; }

[ \t\n] { ; } /* ignore space, tab, and line return */
";" { printf("lex::PT_VIRG %s\n\n",yytext); return PT_VIRG; }

. { printf("lex::char %s\n",yytext); return yytext[0]; } /* other one-char = token, ex. '+' */


"//".* {} /* uniline comment */
"/*" {BEGIN COMMENT;} /* multiline comment */
<COMMENT>\n {}
<COMMENT>"*/" {BEGIN INITIAL;}
<COMMENT>. {}

%% 

