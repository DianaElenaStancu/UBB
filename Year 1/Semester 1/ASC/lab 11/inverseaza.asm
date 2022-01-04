bits 32                         
segment code use32 public code
global inverseaza

inverseaza:
    mov esi, [esp+4];salvam in esi adresa la care se afla cifrele in hexa
    dec edi; in edi este salvata adresa la care se termina sirul de cifre in hexa 
    cld; setam DF = 0
    .repeta:
        mov al, byte [esi] ;se interschimba valorile din capetele sirului
        mov dl, byte [edi]
        mov [esi], dl
        mov [edi], al
        inc esi
        dec edi
        cmp esi, edi
        jae .sfarsit
    jmp .repeta; cat timp esi < edi 
    .sfarsit:
    ret
