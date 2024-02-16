#ifndef CODEASM_H
#define CODEASM_H


#define ADD_ASM_FORMAT "\
\t\tmov al, %s \n\
\t\tadd al, %s \n\
\t\tmov %s, al \n\
" 
#define SUB_ASM_FORMAT "\
\t\tmov al, %s \n\
\t\tsub al, %s \n\
\t\tmov %s, al \n\
" 
#define MUL_ASM_FORMAT "\
\t\tmov al, %s \n\
\t\tmov ah, 0 \n\
\t\tmov dl, %s \n\
\t\tmul dl \n\
\t\tmov %s, al \n\
" 

#define DIV_ASM_FORMAT "\
\t\tmov al, %s \n\
\t\tmov ah, 0 \n\
\t\tmov dl, %s \n\
\t\tdiv dl \n\
\t\tmov %s, al \n\
" 
#define DECL_ASM_FORMAT "\
\t %s times 4 db 0 \n\
" 

#define CIN_ASM_FORMAT "\
\t\tpush dword %s \n\
\t\tpush dword format \n\
\t\tcall [scanf] \n\
\t\tadd ESP, 4 * 2 \n\
" 

#define COUT_ASM_FORMAT "\
\n\t\tpush dword [%s] \n\
\t\tpush dword format \n\
\t\tcall [printf] \n\
\t\tadd ESP, 4 * 2 \n\
" 

#endif
