;a-byte; b-word; e-doubleword; x-qword - intepretare fara semn 
;Problema 21: (a*a/b+b*b)/(2+b)+e-x
;exemplu: (a*a/b+b*b)/(2+b)+e-x = (10*10/25+25*25)/(2+25)+200-1230 = (100/25 + 625)/27+200-1230 = (4+625)/27+200-1230 = 629/27+200-1230 = 23+200-1230 = -1007
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 10
    b dw 25
    e dd 200
    x dq 1230

; our code starts here
segment code use32 class=code
    start:
        mov al, [a]; al = a                             = 10 = 0Ah                                                       
        mul byte [a]; ax = al*a = a*a                   = 100 = 0064h
        
        mov dx, 0; dx:ax = a*a                          = 100 = 0064h
        div word [b]; ax ← dx:x / b = a*a/b             = 4 = 0004h
                    ;dx ← dx:ax % b = a*a%b             = 0 = 0000h
        
        mov bx, ax; bx = a*a/b                          = 4 = 0004h
        mov ax, [b]; ax = b                             = 25 = 0019h
        mul word [b]; dx:ax ← ax * b  = b*b             = 625 = 0000 0271h
        
        mov cx, 0; cx:bx = a*a/b                        = 4 = 0000 0004h
        
        add ax, bx;
        adc dx, cx; dx:ax = a*a/b + b*b                 = 4+625 = 629 = 0000 0275h
        
        mov bx, [b]; bx = b                             = 25 = 0019h
        add bx, 2; bx = 2+b                             = 27 = 001Bh
        div bx; ax ← dx:ax / bx = (a*a/b + b*b)/(2+b)   = 23 = 0017h
              ;dx ← dx:ax % bx = (a*a/b + b*b)%(2+b)    = 8 = 0008h
        
        mov dx, 0; dx:ax = ax = (a*a/b + b*b)/(2+b)     = 23 = 0017h
        add ax, word [e];
        adc dx, word [e+2]; dx:ax = (a*a/b + b*b)/(2+b) + e     = 200+23 = 223 = 0000 00DFh
        
        push dx
        push ax
        pop eax; eax = dx:ax = (a*a/b + b*b)/(2+b) + e          = 223 = 0000 00DFh
        
        mov edx, 0; edx:eax = (a*a/b + b*b)/(2+b) + e           = 223 = 0000 0000 0000 00DFh
        sub eax, dword [x]
        sbb edx, dword [x+4]; edx:eax = (a*a/b + b*b)/(2+b) + e - x = 223-1230 = -1007 = FFFF FFFF FFFF FB11h
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
