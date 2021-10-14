;(f*g-a*b*e)/(h+c*d), a,b,c,d-byte, e,f,g,h-word
;pe exemplu: (f*g-a*b*e)/(h+c*d) =  (25*78-5*2*50)/(32+9*2) = (1950-500)/(32+18) = 1450/50 = 29

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 5
    b db 2
    c db 9
    d db 2
    e dw 50
    f dw 25
    g dw 78
    h dw 32

; our code starts here
segment code use32 class=code
    start:
        mov AX, [f]; AX = f                                                 =25
        mul WORD [g]; DX:AX ← AX * g = f*g                                  =25*78=1950

        push DX;se pune pe stiva partea high din double word-ul DX:AX
        push AX;se pune pe stiva partea low din double word-ul DX:AX
        pop EBX;EBX = DX:AX = f*g                                           =1950

        mov AL, [a]; AL = a                                                 =5
        mul BYTE [b]; AX = AL*b = a*b                                       =5*2=10
        mul WORD [e]; DX:AX ← AX * e = a*b*e                                =10*50=500

        push DX;se pune pe stiva partea high din double word-ul DX:AX
        push AX;se pune pe stiva partea low din double word-ul DX:AX
        pop ECX;ECX = DX:AX = a*b*e                                         =500

        sub EBX, ECX; EBX = EBX-ECX = f*g-a*b*e                             =1950-500=1450

        mov AL, [c]; AL = c                                                 =9
        mul BYTE [d]; AX = AL*d = c*d                                       =9*2=18
        add AX, [h]; AX = AX + h = c*d+h                                    =18+32=50

        mov CX, AX; CX = AX = c*d+h                                         =50
        mov EAX, EBX; EAX = (f*g-a*b*e)                                     =1450

        ;push EAX;
        ;pop AX;
        ;pop DX;

        div CX; EAX ← DX:AX / CX, DX = DX:AX%CX, AX = DX:AX/CX             ;AX = 29, DX = 0
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
