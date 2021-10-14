;(a-b)+(d-c), a, b, c, d - byte
;pe ex: (a-b)+(d-c) = (15-4)+(18-10) = 11+8 = 19
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a db 15
    b db 4
    c db 10
    d db 18
    

; our code starts here
segment code use32 class=code
    start:
        
        mov AL, [a]; AL = a 
        sub AL, [b]; AL = a-b
        mov AH, [d]; AH = d
        sub AH, [c]; AH = d-c
        add AL, AH; AL = AL + AH = (a-b)+(d-c)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
