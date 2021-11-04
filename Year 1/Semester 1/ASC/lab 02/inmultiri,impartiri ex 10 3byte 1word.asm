;3*[20*(b-a+2)-10*c]/5, a,b,c - byte
;pe exemplu: 3*[20*(b-a+2)-10*c]/5 = 3*[20*(25-16+2)-10*13]/5 = 3*(20*11-10*13)/5 = 3*(220-130)/5 = 3*90/5 = 3*90/5 = 54
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    a db 16
    b db 25
    c db 13
    
; our code starts here
segment code use32 class=code
    start:
         
        ;b-a+2
        mov AH, [b]; AH = b                         =25
        sub AH, [a]; AH = b-a                       =25-16=9
        add AH, 2; AH = b-a+2                       =9+2=11

        ;20*(b-a+2)
        mov AL, 20; AH = 20
        mul AH; AX = AH*AL = 20*AL = 20*(b-a+2)     =20*11=220

        mov BX, AX; BX = AX = 20*(b-a+2)            =220

        ;10*c
        mov AL, 10; AL = c                          =13
        mul BYTE [c]; AX = AL*c = 10*c              =130

        ;20*(b-a+2)-10*c
        sub BX, AX; BX = BX-AX = 20*(b-a+2)-10*c    =90

        mov AX, BX; DX = BX = 20*(b-a+2)-10*c       =90

        ;3*[20*(b-a+2)-10*c]/5
        mov BL, 5; BL = 5
        div BL; AL = AL/5 = [20*(b-a+2)-10*c]/5; AH = [20*(b-a+2)-10*c]%5  (AL = CATUL, AH = REST); AL = 18, AH = 0
        mov BL, 3; BL = 3
        mul BL; AX = AL*BL = [20*(b-a+2)-10*c]/5*3  =54
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
