;d-[3*(a+b+2)-5*(c+2)], a,b,c - byte, d - word
;pe exemplu: d-[3*(a+b+2)-5*(c+2)] = 100-[3*(11+7+2)-5*(5+2)] = 100-(3*20-5*7) = 100-(60-35) = 100-25 = 75
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a db 11
    b db 7
    c db 5
    d dw 100

; our code starts here
segment code use32 class=code
    start:
        mov AH, [a]; AL = a                                 =11
        add AH, [b]; AL = a+b                               =11+7=18
        add AH, 2; AL = a+b+2                               =18+2=20

        mov AL, 3; AH = 3
        mul AH; AX = AL*AH = 3*(a+b+2)                      =3*20=60

        mov BX, AX; BX = AX = 3*(a+b+2)                     =60

        mov AH, [c]; AH = c                                 =5
        add AH, 2; AH = c+2                                 =5+2=7

        mov AL, 5;AL = 5
        mul AH; AX = AL*AH = 5*(c+2)                        =5*7=35

        sub BX, AX; BX = BX-AX = 3*(a+b+2)-5*(c+2)          =60-35=25

        mov AX, [d]; AX = d                                 =100
        sub AX, BX; AX = AX-BX = d-[3*(a+b+2)-5*(c+2)]      =100-25=75
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
