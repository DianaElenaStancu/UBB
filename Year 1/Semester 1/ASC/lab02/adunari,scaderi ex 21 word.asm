bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
; a-c+d-7+b-(2+d), a, b, c, d - word
; a-c+d-7+b-(2+d) = 17-10+8-7+22-(2+8) = 30-10 = 20
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 17
    b dw 22
    c dw 10
    d dw 8

; our code starts here
segment code use32 class=code
    start:
        
        ;a-c+d-7+b
        mov AX, [a]; AX = a                     =17
        sub AX, [c]; AX = AX-c = a-c            =17-10=7
        add AX, [d]; AX = AX+d = a-c+d          =7+8=15
        sub AX, 7; AX = AX-7 = a-c+d-7          =15-7=8
        add AX, [b]; AX = AX+b = a-c+d-7+b      =8+22=30

        ;(2+d)
        mov BX, 2; BX = 2
        add BX, [d]; BX = BX+d = 2+d            =2+8=10

        ;a-c+d-7+b-(2+d)
        sub AX, BX; AX = AX-BX = a-c+d-7+b-(2+d) =30-10=20
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
