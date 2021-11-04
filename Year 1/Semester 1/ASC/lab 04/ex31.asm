;Se dau cuvintele A, B si C. Sa se formeze cuvantul D ca suma a numerelor reprezentate de:
;biţii de pe poziţiile 1-5 ai lui A
;biţii de pe poziţiile 6-10 ai lui B
;biţii de pe poziţiile 11-15 ai lui C
;exemplu:
;a = 0110 0011 0111 1100b = 637Dh => numarul obtinut din bitii de pe pozitiile 1-5 este  
                                     ;11110b -> 0000 0000 0001 1110b = 001Eh = 30
;b = 0000 0110 0101 1011b = 065Bh => numarul obtinut din bitii de pe pozitiile 6-10 este
                                     ;11001b -> 0000 0000 0001 1001b = 0019h = 25
;c = 0111 1111 1111 0110b = 7ff6h => numarul obtinut din bitii de pe pozitiile 11-15 este
                                     ;01111b -> 0000 0000 0000 1111b = 000Fh = 15
;d = 0000 0000 0001 1110b+
    ;0000 0000 0001 1001b
    ;0000 0000 0000 1111b = 
   ;=0000 0000 0100 0110b = 46h = 70 (=30+25+15)

bits 32 ; assembling for the 32 bits architecture
    
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0110001101111100b; = 637Dh
    b dw 0000011001011011b; = 065Bh
    c dw 0111111111110110b; = 7ff6h
    d dw 0;= 0000 0000 0000 0000b = 0000h

; our code starts here
segment code use32 class=code
    start:
        ;vom calcula rezultatul in registrul bx 
        mov bx, 0; bx = 0000 0000 0000 0000b = 0000h
        
        ;obtinem numarul din biţii de pe poziţiile 1-5 ai lui A
        mov ax, [a]; izolam bitii 1-5 a lui a = 0110 0011 0111 1100b = 6379h
        and ax, 0000000000111110b; ax = 0000 0000 0011 1100b = 0039h
        ; diferenta dintre b1-b0 o vom pune in cl
        mov cl, 1; cl = 0000 0001b = 01h
        ;rotim cu o pozitie spre dreapta
        ror ax, cl; ax = 0000 0000 0001 1110b = 001Eh = 30
        
        ;adunam lui bx valoarea numarului obtinut din bitii 1-5 a lui a
        add bx, ax; bx = bx + ax = 0000h + 001Eh = 001Eh = 0000 0000 0001 1110b
        
        ;obtinem numarul din biţii de pe poziţiile 6-10 ai lui B
        mov ax, [b]; izolam bitii 6-10 a lui b = 0000 0110 0101 1011b = 065Bh
        and ax, 0000011111000000b; ax = 0000 0110 0100 0000b = 0640h
        ;diferenta dintre b6-b0 o vom pune in cl 
        mov cl, 6; cl = 0000 0110b = 06h 
        ;rotim cu 6 pozitii spre dreapta 
        ror ax, cl; ax = 0000 0000 0001 1001b = 0019h = 25

        ;adunam lui bx valoarea numarului obtinut din bitii 6-10 a lui b 
        add bx, ax; bx = bx + ax = 0000 0000 0001 1110b + 0000 0000 0001 1001b = 0000 0000 0011 0111b = 37h = 55
        
        ;obtinem numarul din bitii de pe pozitiile 11-15 a lui C 
        mov ax, [c]; izolam bitii 11-15 a lui c = 0111 1111 1111 0110b = 7ff6h
        and ax, 1111100000000000b; ax = 0111 1000 0000 0000b = 7800h 
        ;diferenta dintre b11-b0 o vom pune in cl
        mov cl, 11; cl = 0000 1111b = 0Fh
        ;rotim cu 15 pozitii spre dreapta 
        ror ax, cl; ax = 0000 0000 0000 1111b = 000Fh = 15
        
        ;adunam lui bx valoarea numarului din bitii 11-15 a lui C 
        add bx, ax; bx = bx + ax = 0000 0000 0011 0111b + 0000 0000 0000 1111b = 0000 0000 0100 0110b = 0046h = 70
        
        mov [d], bx; d = 0000 0000 0100 0110b = 0046h = 70
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
