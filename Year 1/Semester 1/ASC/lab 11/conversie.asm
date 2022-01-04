bits 32                         
segment code use32 public code
global conversie

conversie: 
	;numarul va fi impartit in grupe de cate 4 biti incepand de la dreapta spre stanga 
    ;cu precizarea ca este posibil ca ultima grupa formata sa nu fie compusa din 4 biti 
    ;acest fapt neinfluentand furnizarea raspunsului corect
    ;numarul in binar format din cei 4 biti va fi convertit conform formulei:
    ;abcd(2) = a*2^3 + b*2^2 + c*2^1 + d*2^0
    mov ecx, [esp+4]; salvam in ecx nr in binar
    mov edi, [esp+8]; salvam in edi adresa la care inseram cifrele in hexa
    mov al, '0'; initializam valoarea din al cu caracterul 0
    cld; setam DF = 0
    jecxz .sfarsit ;daca valoarea lui ecx = 0 va sari direct la eticheta .sfarsit
    .repeta:
        mov al, 1; in al sunt stocate pe rand puterile lui 2
        mov dl, 0; se va afla valoarea in ASCII a caracterului in hexa aferent grupului format din cifre binare
        .convert:
            shr ecx, 1; rotim spre dreapta cu o pozitie bitii din ecx, bitul cel mai din dreapta va fi stocat in CF
            jc .aduna
                jmp .zero
            .aduna:; daca CF = 1, atunci adunam puterea lui 2 aferenta
                add dl, al
            .zero:
            mov bl, 2
            mul bl; ax <- al*bl
            ; stiind ca puterea lui 2 nu poate fi mai mare decat 2^8 ne vom raporta mereu la valoarea din al
            cmp al, 16; ne oprim dupa ce am parcurs cei 4 biti
            jecxz .sf
            je .sf
        jmp .convert
    .sf:
        cmp dl, 10
        jb .cifra
        ; daca dl >= 10 --> 'A', 'B', 'C', 'D', 'E', 'F'
        mov al, dl; din inmultirile anterioare stim ca ah = 0
        mov bl, 10
        div bl; al ← ax / bl, ah ← ax % bl
        mov al, ah; pastram restul
        add al, 'A'; adaugam valoarea in ASCII a caracterului 'A'
        jmp .adaugaCaracter
        .cifra:; daca dl < 10 --> '0','1','2','3','4','5','6','7','8','9'
            add dl, '0'; adaugam valoarea in ASCII a caracterului '0'
            mov al, dl
        .adaugaCaracter:
            stosb ;	La adresa <ES:EDI> se incarcă octetul din AL, inc(EDI)
        jecxz .final
    jmp .repeta
    .sfarsit:
        stosb
    .final:
	ret
