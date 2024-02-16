%{

#include "activitate.tab.h"

%}

%option noyywrap
DIGIT [0-9]
%%
{DIGIT} {
yylval = *yytext - '0';
return DIGIT;
}
":" {return NEXT;}
%%
