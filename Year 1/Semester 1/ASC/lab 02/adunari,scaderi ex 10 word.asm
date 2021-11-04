; b+c+d+a-(d+c), a, b, c, d - word
; b+c+d+a-(d+c) =  10+5+7+26-(7+5) = 48-12 = 36
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a dw 26
    b dw 10
    c dw 5
    d dw 7

; our code starts here
segment code use32 class=code
    start:
        
        mov AX, [b]; AX = b                         =10
        add AX, [c]; AX = AX+c = b+c                =10+5=15
        add AX, [d]; AX = AX+d = b+c+d              =15+7=22
        add AX, [a]; AX = AX+a = b+c+d+a            =22+26=48

        mov BX, [d]; BX = d                         =7
        add BX, [c]; BX = BX+c = d+c                =7+5=12

        sub AX, BX; AX = AX-BX = b+c+d+a - (d+c)    =48-12 = 36
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
