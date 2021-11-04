;Sa se inlocuiasca bitii 0-3 ai octetului B cu bitii 8-11 ai cuvantului A.
;exemplu: 
;a = 0111 0111 0110 1101b = 776Dh
;b = 1001 1011b = 9Bh
;b(0-3) = a(8-11)
;b = 1001 0111b = 97h

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
     a dw 0111011101101101b; =776Dh
     b db 10011011b; =9Bh
; our code starts here
segment code use32 class=code
    start:
        ; in registrul bl vom calcula rezultatul
        mov bl, 0; bl = 0000 0000b = 00h
        
        ; izolam bitii 8-11 ai lui a 
        mov ax, [a]; ax = a = 0111 0111 0110 1101b = 776Dh
        and ax, 0000111100000000b; ax = a = 0000 0111 0000 0000b = 0700h
        
        ; diferenta dintre b8 si b0 o vom pune in cl
        mov cl, 8; cl = 0000 1000b = 08h
        
        ;rotim 8 pozitii spre dreapta, in acest mod am pus bitii 8-11 in partea low a registrului ax    
        ror ax, cl; ax = 0000 0000 0000 0111b = 0007h

        ; punem bitii in rezultat 
        or bl, al; bl = 0000 0111b = 07h
        
        ;inlocuim bitii 0-3 ai octetului b cu bitii 8-11 ai lui a 
        mov al, [b]; al = b = 1001 1011b = 9Bh
        ;izolam bitii 4-7, cei care nu trebuie inlocuiti
        and al, 11110000b; al = 1001 0000b = 90h
        ;punem bitii in rezultat 
        or bl, al; bl = 1001 0111b = 97h
        
        mov [b], bl; b = 1001 0111b = 97h
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
