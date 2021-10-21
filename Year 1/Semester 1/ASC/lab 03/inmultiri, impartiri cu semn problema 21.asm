;a-byte; b-word; e-doubleword; x-qword - intepretare cu semn  
;Problema 21: (a*a/b+b*b)/(2+b)+e-x
;exemplu: (a*a/b+b*b)/(2+b)+e-x = ((-16)*(-16)/(-4)+(-4)*(-4))/(2+(-4))+200-(-1234) = =((-16)*(-16)/(-4)+(-4)*(-4))/(2+(-4))+200-(-1234) = (256/(-4) + 16)/(-2) + 200 -(-1234) = (-64+16)/(-2)+200-(-1234) = (-48)/(-2)+200-(-1234) = 24+200+1234 = 224+1234 = 1458
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db -16
    b dw -4
    e dd 200
    x dq -1234
; our code starts here
segment code use32 class=code
    start:
        mov ax, [b]; ax = b                                         = -4 = FFFCh
        imul word [b]; dx:ax = b*b                                  = 16 = 0000 0010h
        mov cx, dx
        mov bx, ax; cx:bx = dx:ax = b*b                             = 16 = 0000 0010h
        
        mov al, [a]; al = a                                         = -16 = F0h
        imul byte [a]; ax = al*a = a*a                              = (-16)*(-16) = 256 = 0100h
        cwd; dx:ax = a*a                                            = 256 = 0000 0100h
        idiv word [b]; ax ← dx:ax/b  = a*a/b                        = 256/(-4) = -64 = FFC0h
                     ; dx ← dx:ax%b = a*a%b                         = 0 = 0000h
        cwd; dx:ax = a*a/b                                          = -64 = FFFF FFC0h
        
        add ax, bx
        adc dx, cx; dx:ax = (a*a/b + b*b)                           = -64+16 = -48 = FFFF FFD0h
        
        mov bx, [b]; bx = b                                         = -4 = FFFCh  
        add bx, 2; bx = b + 2                                       = -2 = FFFEh
        idiv bx; ax ← dx:ax/bx  = (a*a/b + b*b)/(b+2)               = (-48)/(-2) = 24 = 0018h
               ; dx ← dx:ax%b = (a*a/b + b*b)%(b+2)                 = (-48)%(-2) = 0 = 0000h
        
        cwd; dx:ax = (a*a/b + b*b)/(b+2)                            = 24 = 0000 0018h
        add ax, [e]
        adc ax, [e+2]; dx:ax = (a*a/b + b*b)/(b+2) + e              = 24+200 = 224 = 0000 00E0h 
        cdq; edx:eax = (a*a/b + b*b)/(b+2) + e                      = 224 = 0000 0000 0000 00E0h
        
        sub eax, [x]
        sbb edx, [x+4]; edx:eax=(a*a/b + b*b)/(b+2)+e-x   = 224-(-1234) = 224+1234 = 1458 = 0000 0000 0000 05B2h
        
        ;intrebare: am facut o impartire si in ax se pune catul in dx se pune restul si vreau sa convertesc catul de tip word in tip dword. pot face direct operatia cwd? (o sa se suprascrie?)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
