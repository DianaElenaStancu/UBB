;a*d+b*c, a,b,c,d-byte
;pe exemplu: a*d+b*c = 21*5+4*10 = 105 + 40 = 145

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
        mul BYTE [d]; AX = AL*d = a*d
        
        mov BX, AX; BX = AX = a*d
        
        mov AL, [b]; AL = b 
        mul BYTE [c]; AX = AL*c = b*c 
        
        add BX, AX; BX = BX + AX = a*d + b*c
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
