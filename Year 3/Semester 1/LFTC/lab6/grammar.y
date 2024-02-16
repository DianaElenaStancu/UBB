%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "codeASM.h"
#include "attrib.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror();    

FILE* outputFile;
char* filename;

#define MAX 10000

char var[MAX][MAX];
int tempnr = 1;
int varLen = 0;
void newTempName(char* s){
  sprintf(s,"[temp%d]",tempnr);
  strcpy(var[varLen], s);
  varLen++;
  tempnr++;
}

char tempbuffer[MAX];

int lineno = 1;

char *result;
%}

%union {
 char varname[10];
 attributes attrib;
 char strCode[1000];
}

%token INCLUDE
%token INT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token ASSIGN
%token COMMA
%token SEMICOLON
%token LBR
%token RBR
%token CIN
%token COUT
%token LPR
%token RPR
%token MAIN
%token RETURN

%token <varname> ID
%token <varname> CONST 
%type <attrib> term
%type <attrib> factor
%type <attrib> expression
%type <attrib> program
%type <attrib> antet
%type <attrib> code_segment
%type <attrib> data_segment
%type <attrib> instr_decl
%type <attrib> instr_cin
%type <attrib> instr_cout
%type <attrib> instr_assign
%type <attrib> instr
%type <attrib> instr_list

%%
program: antet LBR data_segment code_segment RBR
        {
          strcpy($$.code, "bits 32\nglobal start\n\nextern exit\nimport exit msvcrt.dll\nextern scanf\nimport scanf msvcrt.dll\nextern printf\nimport printf msvcrt.dll\n\n");

          //data segment
          strcat($$.code, "segment data use32 class=data\n\tformat db \"%d\", 0\n");
          strcat($$.code, $3.code);
          for (int i = 0; i < varLen; i++) {
            if (var[i][0] == '[') {
              strcpy(var[i], var[i] + 1);
              int len = strlen(var[i]);
              var[i][len - 1] = '\0';
            }
            sprintf(tempbuffer, DECL_ASM_FORMAT, var[i]);
            strcat($$.code, tempbuffer);
          }


          strcat($$.code, "\n");
          strcat($$.code, $4.code);

          printf("Assembly code:\n\n%s\n",$$.code);
          result = strdup($$.code);
        }
        ;

antet: INCLUDE INT MAIN
      {
        strcpy($$.code, "");
        strcpy($$.varn, "");
      }
      ;

data_segment: instr_decl | data_segment instr_decl 
      ;

instr_decl: INT ID SEMICOLON 
            {
              strcpy(var[varLen], $2);
              varLen++;
            }
            ;

code_segment: instr_list RETURN
      {
        strcpy($$.code, "segment code use32 class=code\n\tstart:\n");
        strcat($$.code, $1.code);
        strcat($$.code, "\n\t\tpush dword 0\n\t\tcall [exit]");
      }
      ;

instr_list: instr 
            {
              strcpy($$.code, $1.code);
            }
            | instr_list instr
            {
              strcat($$.code, $2.code);
            }
;

instr: instr_cin 
      {
        sprintf(tempbuffer, CIN_ASM_FORMAT, $1.varn);
        strcat($$.code,tempbuffer);
      }
      | instr_cout 
      {
        sprintf(tempbuffer, COUT_ASM_FORMAT, $1.varn);
        strcat($$.code,tempbuffer);
      }
      | instr_assign
      {
        strcpy($$.code, $1.code);
      }
      ;


instr_cin: CIN ID SEMICOLON
          {
            strcpy($$.varn, $2);
          }
        ;

instr_cout: COUT ID SEMICOLON
          {
            strcpy($$.varn, $2);
          }
        ;                        
				
instr_assign    : ID ASSIGN expression SEMICOLON
                  {
                    strcpy($$.code, $3.code);

                    sprintf(tempbuffer,"\t\tmov al, %s\n\t\tmov [%s], al\n",$3.varn, $1);
                    strcat($$.code,tempbuffer);
                  }
                ;


expression      : term {
                      strcpy($$.code,$1.code);
                      strcpy($$.varn,$1.varn);
                       }
                | expression PLUS term { 
                     newTempName($$.varn);
                     sprintf($$.code,"%s\n%s\n",$1.code,$3.code);
                     sprintf(tempbuffer,ADD_ASM_FORMAT,$1.varn,$3.varn,$$.varn);
                     strcat($$.code,tempbuffer);
                     }
                | expression MINUS term { 
                     newTempName($$.varn);
                     sprintf($$.code,"%s\n%s\n",$1.code,$3.code);
                     sprintf(tempbuffer,SUB_ASM_FORMAT,$1.varn,$3.varn,$$.varn);
                     strcat($$.code,tempbuffer);
                     }
                ;

term: term MULTIPLY factor 
      {
                     newTempName($$.varn);
                     sprintf($$.code,"%s\n%s\n",$1.code,$3.code);
                     sprintf(tempbuffer, MUL_ASM_FORMAT,$1.varn,$3.varn,$$.varn);
                     strcat($$.code,tempbuffer);
      }
      | term DIVIDE factor
      {
                     newTempName($$.varn);
                     sprintf($$.code,"%s\n%s\n",$1.code,$3.code);
                     sprintf(tempbuffer, DIV_ASM_FORMAT,$1.varn,$3.varn,$$.varn);
                     strcat($$.code,tempbuffer);
      }
      | factor
      {

      }

factor            : CONST {
                      strcpy($$.code,"");
                      strcpy($$.varn,$1); 
                      }
                | ID { 
                        strcpy($$.code,"");
                        sprintf($$.varn, "[%s]", $1);
                        //strcpy($$.varn,$1); 
                      }
                | LPR expression RPR {
                        strcpy($$.code, $2.code);
                        strcpy($$.varn,$2.varn);
                      }
                     
                ;
;

%%

int main(int argc, char* argv[]) {
	FILE* f = NULL;
    if (argc > 1) { 
        f = fopen(argv[1], "r");
    }

	if (!f) {
		perror("Could not open file! Switching to console...\n");
		yyin = stdin;
	} else {
		yyin = f;
	}
     	
	while (!feof(yyin)) {
		yyparse();
	}

  char fileName[100];
  strcpy(fileName, argv[1]);
  fileName[strlen(fileName) - 3] = '\0';
  strcat(fileName, "asm");
  printf(fileName);

	printf("The file is sintactically correct!\n");
    
  FILE *file = fopen(fileName, "w");

  int results = fputs(result, file);
  if (results == EOF) {
    //error
  }
  fclose(file);

	return 0;
}

void yyerror() {
	extern char* yytext;
	printf("Error for symbol %s on line: %d\n", yytext, lineno);
	exit(1);
}
