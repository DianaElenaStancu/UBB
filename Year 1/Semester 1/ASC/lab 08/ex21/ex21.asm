;Sa se citeasca de la tastatura doua numere a si b de tip word. Sa se afiseze in baza 16 numarul c de tip dword pentru care partea low este suma celor doua numere, iar partea high este diferenta celor doua numere. Exemplu:
;a = 574, b = 136
;c = 01B602C6h


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll    ; indicam asamblorului ca functia printf se gaseste in libraria msvcrt.dll
import scanf msvcrt.dll    ; similar pentru scanf

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0
    s1 dw 0;ocupam spatii goale de 0 
    b dw 0
    s2 dw 0
    c dd 0
    message1 db "a = ", 0
    message2 db "b = ", 0
    message3 db "c = %X", 0
    formatdec db "%d", 0

; our code starts here
segment code use32 class=code
    start:
        ;vom apela printf(message1)
        push dword message1; pe stiva se pune adresa stringului 
        call [printf]
        add esp, 4*1;eliberam parametrii de pe stiva
    
        ; vom apela functia scanf(formatdec, a)
        push dword a 
        push dword formatdec 
        call [scanf]
        add esp, 4*2 
        
        ;vom apela printf(message2)
        push dword message2; pe stiva se pune adresa stringului 
        call [printf]
        add esp, 4*1;eliberam parametrii de pe stiva
    
        ; vom apela functia scanf(formatdec, b)
        push dword b 
        push dword formatdec 
        call [scanf]
        add esp, 4*2 
        
        ;calculam partea low a numarului c care este formata din suma celor doua numere: a + b
        mov ax, [a] 
        add ax, [b] 
        
        ;calculam partea high a numarului c care este formata din diferenta celor doua numere: a - b
        mov dx, [a] 
        sub dx, [b] 

        push dx
        push ax
        pop dword[c]; c = dx:ax
        
        ;apelam functia printf(message3, c)
        push dword [c] 
        push dword message3
        call [printf]
        add esp, 4*2
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
