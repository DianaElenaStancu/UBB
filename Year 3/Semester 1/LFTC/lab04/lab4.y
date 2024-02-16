%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern void printTs();
extern FILE* yyin;
extern int currentLine;
void yyerror();

%}

%token INCLUDE_MAIN
%token RETURN
%token FLOAT
%token INT
%token STR
%token IF
%token ELSE
%token WHILE
%token CIN
%token COUT
%token ENDL
%token SEMICOLON
%token OPEN_PAREN
%token CLOSE_PAREN
%token OPEN_SQ
%token CLOSE_SQ
%token OPEN_BRACE
%token CLOSE_BRACE
%token SHIFT_LEFT
%token SHIFT_RIGHT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token MODULO
%token ASSIGN
%token GREATER_EQUAL
%token EQUAL
%token NOT_EQUAL
%token LESS_EQUAL
%token GREATER
%token LESS
%token ID
%token CONST
%token DIGIT_0
%token DIGIT
%token BINARY_DIGIT
%token OCTAL_DIGIT
%token HEX_DIGIT


%%

program: antet instructiuni_main
	;

antet: INCLUDE_MAIN
	;

instructiuni_main: OPEN_BRACE instructiune_lista CLOSE_BRACE
    ;

instructiune_lista: instructiune | instructiune instructiune_lista
    ;

instructiune: instr_citire | instr_afisare | instr_declarare | instr_atribuire | instr_if | RETURN
    ;

instr_citire: CIN SHIFT_RIGHT ID SEMICOLON
    ;

instr_afisare: COUT SHIFT_LEFT ID SEMICOLON | COUT SHIFT_LEFT CONST SEMICOLON
    ;

instr_declarare: tip ID SEMICOLON
    ;

tip: FLOAT | INT | STR
    ;

instr_atribuire: ID ASSIGN expresie SEMICOLON
    ;

expresie: variabila op_arit expresie | CONST op_arit expresie | variabila | CONST_INT
    ;

variabila: ID | ID OPEN_SQ CONST CLOSE_SQ
    ;

CONST_INT: MINUS CONST | CONST
    ;

op_arit: PLUS | MINUS | DIVIDE | MULTIPLY | MODULO
    ;

instr_if: IF OPEN_PAREN conditie CLOSE_PAREN OPEN_BRACE instructiune_lista CLOSE_BRACE
    ;

conditie: variabila op_comp variabila | variabila op_comp CONST | CONST op_comp variabila
    ;

op_comp: GREATER_EQUAL | EQUAL | NOT_EQUAL | LESS_EQUAL | GREATER | LESS
    ;
%%

int main(int argc, char* argv[]) {
	++argv, --argc;

    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    while (!feof(yyin)) {
		printf("---------------------------FIP--------------------------\n");
        yyparse();
    }
	printf("----------------------------TS----------------------------\n");
	printTs();
    printf("The file is sintactically correct!\n");
    return 0;
}

void yyerror() {
	extern char* yytext;
	printTs();
	printf("Error for symbol %s on line: %d\n", yytext, currentLine);
	exit(1);
}