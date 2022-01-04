bits 32
global _conversie
segment data public data use32
    sir db 'un sir'
segment code public code use32
_conversie:
    ;crearea cadrului de stiva
    push ebp
	mov ebp,esp     
    ;[esp] - ebp
    ;[esp+4*1] - adresa de return 
    ;[esp+4*2] - nr binar
    ;[esp+4*3] - adresa sir hexa
   
    ;conversia
    mov ecx, [esp + 4*2]; salvam in ecx numarul in Binar
    mov edi, [esp + 4*3]; salvam in edi adresa la care inseram cifrele in hexa
        mov al, '0'; initializam valoarea din dl cu caracterul 0
    cld
    jecxz .sfarsit ;daca valoarea lui ecx = 0 va sari direct la eticheta .sfarsit

    .repeta:
        mov al, 1; in al sunt stocate pe rand puterile lui 2
        mov dl, 0; se afla valoarea in ASCII a caracterului in hexa aferent grupului format din cifre binare
        .convert:
            shr ecx, 1; rotim spre dreapta cu o pozitie bitii din ecx, bitul cel mai din dreapta va fi stocat in CF
            jc .aduna
                jmp .zero
            .aduna:; daca CF = 1, atunci adunam puterea lui 2 aferenta
                add dl, al
            .zero:
            mov bl, 2
            mul bl; ax <- al*bl
            ; stiind ca puterea lui 2 nu poate fi mai mare decat 2^8 vom inmulti mereu la al
            cmp al, 16; ne oprim dupa ce am parcurs cei 4 biti
            jecxz .sf
            je .sf
        jmp .convert
    .sf:
        cmp dl, 10
        jb .cifra
        mov al, dl
        mov bl, 10
        div bl
        mov al, ah
        add al, 'A'
        jmp .adaugaCaracter
        .cifra:; daca dl < 10
            add dl, '0'
            mov al, dl
        .adaugaCaracter:
            stosb
        jecxz .final
    jmp .repeta
    .sfarsit:
        stosb;la adresa <ES:EDI> se incarcă octetul din AL
    .final:
    
    ;revenirea din procedura
    mov esp, ebp
    pop ebp
	ret