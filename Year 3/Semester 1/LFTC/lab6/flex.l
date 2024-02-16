%{
#include <string.h> /* for strcpy */

#include "attrib.h"
#include "grammar.tab.h" /* token type definitions from .y file */

extern int lineno;  /* defined in micro.y */

%}

DIGIT_0 [1-9]
DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

"#include<iostream> using namespace std;"   return INCLUDE; 
int                                         return INT;
"+"                                         return PLUS;
"-"                                         return MINUS; 
"*"                                         return MULTIPLY; 
"/"                                         return DIVIDE; 
"="                                         return ASSIGN; 
","                                         return COMMA; 
";"                                         return SEMICOLON; 
"{"                                         return LBR; 
"}"                                         return RBR; 
"cin >>"                                    return CIN; 
"cout <<"                                   return COUT; 
"("                                         return LPR; 
")"                                         return RPR; 
"main()"                                    return MAIN; 
"return 0;"                                 return RETURN; 

{ID} { strcpy(yylval.varname,yytext); return ID; }

0|{DIGIT_0}{DIGIT}* { strcpy(yylval.varname,yytext); return CONST; }

[\n] { lineno++; }

[ \t\r] /* ignore white spaces */

.                       { 
                        printf( "My: Illegal character \n %s \n on line #%d\n",
                                yytext,lineno);
                        
                        }

%%

int yywrap() {
  return 1; /* tell scanner no further files need to be processed */
}