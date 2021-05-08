/* file lexeur.l */ 
/* compilation: flex lexeur.l */
/* result: lex.yy.c = lexical analyser in C */

%{
 #include <stdio.h>       /* printf */
 #include "parseur.tab.h" /* token constants def. in parseur.y via #define */
%}

%%

0|[1-9][0-9]*(\.[0-9]+)? { printf("lex::NOMBRE %s\n",yytext); yylval.doubleVal=atof(yytext);  return NOMBRE; }
[ \t\n] { ; } /* ignore space, tab, and line return */
";" { printf("lex::PT_VIRG %s\n\n",yytext); return PT_VIRG; }

. { printf("lex::char %s\n",yytext); return yytext[0]; } /* other one-char = token, ex. '+' */


%% 
