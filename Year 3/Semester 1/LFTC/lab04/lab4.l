%{

#include "lab4.tab.h"
int currentLine = 1;

typedef struct {
	char* name;
	int code;
} Atom;

int count = 0;
int lineNumber = 0;
Atom ts[100];

    Atom atomsCode[] = {
        // Keywords
        {"include <iostream> using namespace std; int main()", 0},
        {"return 0;", 1},
        {"float", 2},
        {"int", 3},
        {"if", 4},
        {"else", 5},
        {"while", 6},
        {"cin", 7},
        {"cout", 8},
        {"endl", 9},

        // Separators
        {";", 10},
        {"(", 11},
        {")", 12},
        {"{", 13},
        {"}", 14},
        {"<<", 15},
        {">>", 16},

        // Algebraic Operators
        {"+", 17},
        {"-", 18},
        {"*", 19},
        {"/", 20},
        {"%", 21},
        {"=", 22},

        // Relational Operators
        {">=", 23},
        {"==", 24},
        {"!=", 25},
        {"<=", 26},
        {">", 27},
        {"<", 28},
        {"ID", 29},
        {"CONST", 30},
        {"string", 31},
        {"[", 32},
        {"]", 33}
    };

int getAtomsCode(char* key) {
	for (int i = 0; i < 39; ++i) {
		if (strcmp(atomsCode[i].name, key) == 0) {
			return atomsCode[i].code;
		}
	}
}

int getCodeTs(char* key) {
	for (int i = 0; i < count; ++i) {
		if (strcmp(ts[i].name, key) == 0) {
			return ts[i].code;
		}
	}

	return -1;
}

void addToTs(char* atom) {
	int index = 0;

	while (index < count && strcmp(ts[index].name, atom) < 0) {
		++index;
	}

	if (index < count && strcmp(ts[index].name, atom) == 0) {
		return;
	}

	for (int i = count; i > index; --i) {
		ts[i] = ts[i - 1];
	}

	ts[index].name = malloc(strlen(atom) + 1);
	strcpy(ts[index].name, atom);
	ts[index].code = count;

	count++;
}

void printTs() {
    for(int i = 0; i < count; i++){
		printf("%s %d\n", ts[i].name, ts[i].code);
    }
}

%}

%option noyywrap

DIGIT_0 [1-9]
DIGIT       [0-9]
BINARY_DIGIT [01]
OCTAL_DIGIT [0-7]
HEX_DIGIT   [0-9A-Fa-f]
ID          [a-zA-Z_][a-zA-Z0-9_]*
CONST_INT           0|([1-9]([0-9]*))
CONST_REAL          {CONST_INT}"."[0-9]+
CONST_BINARY        "0b"[01]+
CONST_HEXA          "0x"[0-9A-F]+
CONST_OCTAL         "0"[0-7]+
CONST               {CONST_INT}|{CONST_REAL}|{CONST_BINARY}|{CONST_HEXA}|{CONST_OCTAL}

%%

"include <iostream> using namespace std; int main()"   { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return INCLUDE_MAIN; }
"return 0;"         { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return RETURN; }
float           { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return FLOAT; }
int             { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return INT; }
string             { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return STR; }
if              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return IF; }
else            { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return ELSE; }
while           { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return WHILE; }
cin             { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return CIN; }
cout            { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return COUT; }
endl            { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return ENDL; }

";"               { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return SEMICOLON; }
"("              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return OPEN_PAREN; }
")"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return CLOSE_PAREN; }
"["              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return OPEN_SQ; }
"]"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return CLOSE_SQ; }
"{"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return OPEN_BRACE; }
"}"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return CLOSE_BRACE; }
"<<"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return SHIFT_LEFT; }
">>"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return SHIFT_RIGHT; }

"+"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return PLUS; }
"-"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return MINUS; }
"*"              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return MULTIPLY; }
"/"               { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return DIVIDE; }
"%"               { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return MODULO; }
"="               { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return ASSIGN; }

">="              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return GREATER_EQUAL; }
"=="              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return EQUAL; }
"!="              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return NOT_EQUAL; }
"<="              { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return LESS_EQUAL; }
">"               { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return GREATER; }
"<"               { printf(" %s  %d\n", yytext, getAtomsCode(yytext)); return LESS; }


{ID} {
    int i = getCodeTs(yytext);
	if (i == -1) {
		addToTs(yytext);
	}
    printf(" %s  %d poz: %d\n", yytext, getAtomsCode("ID"), i);
    return ID;
}

{CONST} {
    addToTs(yytext);
	printf(" %s  %d poz: %d\n", yytext,getAtomsCode("CONST"), getCodeTs(yytext));
    return CONST;
}

[\n] { currentLine++; }

[ \t]+ ;

%%