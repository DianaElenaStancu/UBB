; (a+d+d)-c+(b+b)  a,b,c,d - byte
;ex: (a+d+d)-c+(b+b) = (21+5+5)-10+(4+4) = 31-10+8 = 29
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a db 21
    b db 4
    c db 10
    d db 5

; our code starts here
segment code use32 class=code
    start:
        
        mov AL, [a]; AL = a 
        add AL, [d]; AL = a+d
        
        add AL, [d]; AL = a+d+d
        sub AL, [c]; AL = (a+d+d)-c 
        
        mov AH, [b]; AH = b
        add AH, [b]; AH = b+b
        
        add AL, AH; AL = AL+AH = (a+d+d)-c+(b+b)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
