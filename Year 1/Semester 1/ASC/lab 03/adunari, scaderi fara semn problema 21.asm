;a - byte, b - word, c - double word, d - qword - Interpretare fara semn
;Problema 21:  (c-a) + (b - d) +d
;Exemplu: (c-a) + (b - d) +d = (120-2) + (25 - 200) +200 = 118 - 175 + 200 = 143
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2
    b dw 25
    c dd 120
    d dq 200

; our code starts here
segment code use32 class=code
    start:
        mov eax, 0; conversie fara semn de la ax la eax
        mov al, [a]; EAX = a                                        = 2 = 0000 0002h
        mov ebx, [c]; ebx = c                                       = 120 = 0000 0078h
        sub ebx, eax; ebx = ebx - eax = c - a                       = 120-2 = 118 = 0000 0076h
        
        mov edx, 0; conversie fara semn de la ax la edx:eax
        mov eax, 0; conversie fara semn de la ax la edx:eax
        mov ax, [b]; edx:eax = b                                    = 25 = 0000 0000 0000 0019h
        sub eax, [d]; 
        sbb edx, [d + 4]; edx:eax = b - d                           = 25-200 = -175 = FFFF FFFF FFFF FF51h
        
        mov ecx, 0; conversie fara semn de la ebx la ecx:ebx = c-a
        add eax, ebx;
        adc edx, ecx; edx:eax = (c-a) + (b-d)                       = 118-175 = -57 = FFFF FFFF FFFF FFC7h
        
        add eax, [d];
        adc edx, [d+4]; edx:eax = (c-a) + (b-d) + d                 = -57 + 200 = 143 = 0000 0000 0000 008Fh
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
