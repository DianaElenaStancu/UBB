;Se dau cuvintele A si B. Se cere dublucuvantul C:
;bitii 0-3 ai lui C coincid cu bitii 5-8 ai lui B
;bitii 4-10 ai lui C sunt invers fata de bitii 0-6 ai lui B
;bitii 11-18 ai lui C sunt 1
;bitii 19-31 ai lui C coincid cu bitii 3-15 ai lui B

;    31-19   18-11         10-4      3-0    
;C = B(15-3) (8 biti de 1) invB(6-0) B(8-5)

;exemplu
;b = 0111 1111 0110 1101b = 7F6Dh
;c = 0111 1111 0110 1111 1111 1001 0010 1011b = 7F6F:F92Bh 

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    b dw 0111111101101101b; = 7F6Dh
    c dd 0;= 0000 0000 0000 0000 0000 0000 0000 0000b = 00000000h 

; our code starts here
segment code use32 class=code
    start:
        ;vom calcula rezultatul in dx:ax
        mov ax, 0; ax = 0000 0000 0000 0000b = 0000h
        mov dx, 0; dx = 0000 0000 0000 0000b = 0000h
        
        ;operatia 1: b3-0 = B(8-5)
        mov bx, [b]; izolam bitii 8-5 a lui b = 0111 1111 0110 1101b = 7F6Dh
        and bx, 0000000111100000b; bx = 0000 0001 0110 0000b = 0160h
        ;diferenta dintre b8 si b0 o vom pune in cl 
        mov cl, 5; cl = 0000 0101b = 05h
        ;rotim cu 5 pozitii spre dreapta 
        ror bx, cl; bx = 0000 0000 0000 1011b = 000Bh
        ;punem bitii in rezultat 
        or ax, bx; ax = 0000 0000 0000 1011b = 000Bh
        
        ;operatia 2: b10-4 = invB(6-0)
        mov bx, [b]; izolam bitii 6-0 a lui b
        not bx; inversam bitii: bx = 1000 0000 1001 0010b = 8092h
        and bx, 0000000001111111b; bx = 0000 0000 0001 0010b = 0012h
        ;diferenta dintre b10 si b6 o vom pune in cl
        mov cl, 4; cl = 0000 0100b = 04h 
        ;rotim cu 4 pozitii la stanga 
        rol bx, cl; bx = 0000 0001 0010 0000b = 0120h
        ;punem bitii in rezultat 
        or ax, bx; ax = 0000 0001 0010 1011b = 012Bh
        
        ;operatia 3: b18-11: 11111111
        ;fortam b11-15 pe valoarea 1
        or ax, 1111100000000000b; ax = 1111 1001 0010 1011b = F92Bh
        ; fortam b16-b18 pe valorea 1
        or dx, 0000000000000111b; dx = 0000 0000 0000 0111b = 0007h
        
        ;operatia 4: b31-19 = B(15-3)
        mov bx, [b]; izolam bitii 15-3 a lui b 
        and bx, 1111111111111000b; bx = 0111 1111 0110 1000b = 7F61h 
        ;punem bitii in rezultat 
        or dx, bx; dx = 0111 1111 0110 1111b = 7F6Fh
        
        ;dx:ax = 0111 1111 0110 1111:1111 1001 0010 1011b = 7F6F:F92Bh
    
        ;mutam dublucuvantul in memorie 
        push dx
        push ax
        pop ecx 
        mov [c], ecx; c = 0111 1111 0110 1111 1111 1001 0010 1011b = 7F6FF92Bh
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
