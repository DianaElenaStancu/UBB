bits 32
global _inverseaza
segment data public data use32
    sir db 'un sir'
segment code public code use32
_inverseaza:
    ;crearea cadrului de stiva
    push ebp
	mov ebp,esp     
    ;[esp] - ebp
    ;[esp+4*1] - adresa de return 
    ;[esp+4*2] - lungimea sirului
    ;[esp+4*3] - adresa sir hexa
   
    ;inverseaza
    mov esi, [esp+4*3]
    mov edi, esi
    add edi, [esp+4*2]
    dec edi
    cld
    .repeta:
        mov al, byte [esi]
        mov dl, byte [edi]
        mov [esi], dl
        mov [edi], al
        inc esi
        dec edi
        cmp esi, edi
        jae .sfarsit
    jmp .repeta
    .sfarsit:
    
    ;revenirea din procedura
    mov esp, ebp
    pop ebp
	ret