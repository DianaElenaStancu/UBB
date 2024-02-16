%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror();

%}

%token DIGIT
%token NEXT

%%
HOUR: DIGIT DIGIT NEXT DIGIT DIGIT {
    if($1 == $5 && $2 == $4) {
        printf("palindrome");
    } else {
        printf("NOT palindrome");
    }
}
;

. {}
;
%%


int main(int argc, char* argv[]) {
	++argv, --argc;

    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    while (!feof(yyin)) {
		yyparse();
    }
    return 0;
}
void yyerror() {
    printf("Error");
	exit(1);
}