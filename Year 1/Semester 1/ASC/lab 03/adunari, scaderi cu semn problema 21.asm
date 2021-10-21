;a - byte, b - word, c - double word, d - qword - Interpretare cu semn
;Problema 21: d-a+(b+a-c)
;Exemplu: d-a+(b+a-c) = d-a+(b+a-c) = 1000 -(-5) + (-30 -(-5)-(-200)) = 1000 -(-5) + (-35-(-200)) = 1000 -(-5) + 165 = 1005 + 165 = 1170

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db -5
    b dw -30
    c dd -200
    d dq 1000

; our code starts here
segment code use32 class=code
    start:
        mov al, [a]; al = a                         = -5 = FBh
        cbw; ax = a                                 = -5 = FFFAh
        add ax, [b]; ax = b+a                       = -30-5 = -35 = FFDDh
        cwd; dx:ax = b+a                            = -35 = FFFF FFDDh
        sub ax, [c];                        
        sbb dx, [c+2]; dx:ax = b+a-c                = -35+200 = 165 = 0000 00A5h
        
        mov cx, dx;
        mov bx, ax; cx:bx = b+a-c
        
        mov al, [a];
        cbw; ax = a
        cwd; dx:ax = a                              = -5 = FFFF FFFBh
        
        sub bx, ax;
        sbb cx, dx;cx:bx = -a + (b+a-c)             = 5+165 = 170 = 0000 00AAh
        
        push cx
        push bx
        pop eax; eax = -a + (b+a-c)                 = 170 = 0000 00AAh
        cdq; edx:eax = -a + (b+a-c)                 = 170 = 0000 0000 0000 00AAh
        
        add eax, [d];
        sbb edx, [d+4]; edx:eax = d-a + (b+a-c)     = 1000+170 = 1170 = 0000 0000 0000 0492h
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
