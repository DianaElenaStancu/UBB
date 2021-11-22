;ex_21(sens invers): Dandu-se un sir de cuvinte sa se obtina sirul (de octeti) cifrelor in baza zece ale fiecarui cuvant din acest sir.
;Exemplu:
;daca avem sirul:
;sir DW 12345, 20778, 4596 
;obtinem rezultatul
;1, 2, 3, 4, 5, 2, 0, 7, 7, 8, 4, 5, 9, 6.
;Solutie: parcurgem fiecare cuvant in sens invers, salvam o copie a numarului si aflam cate cifre are
;in functie de numarul de cifre vom seta adresa de la care sa insereze cifrele numarului pe care urmeaza sa le extragem de la dreapta la stanga 
;pentru a trece la inserarea cifrelor urmatorului numar suntem nevoiti sa revenim la adresa de la care am inceput sa inseram cifrele in sens invers(de la dreapta la stanga)

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir DW 12345, 20778, 4596, 2, 45, 782, 0, 3002
    len equ ($-sir)/2; lungimea sirului in cuvinte
    sir_cifre times len*5 db 0;numarul maxim de cifre pe care le poate avea un cuvant este de 5
    ;Pe 16 biţi se pot reprezenta 2^16 valori = 65536 valori([0..65535] in interpretarea fara semn)
    zece dw 10; variabila folosita pentru determinarea cifrelor numarului prin impartiri succesive 
    ;numerele fiind foarte mari va trebui sa punem fiecare cuvant din sir intr-un dublucuvant si apoi sa il impartim la 10 succesiv 
; our code starts here
segment code use32 class=code
    start:
        mov esi, sir+len*2-2
        mov edi, sir_cifre
        dec edi
        std; parcurgem sirul in sens invers(DF = 1)
        mov ecx, len; vom parcurge elementele sirului
        jecxz sfarsitSir
        repetaSir:
            lodsw; in ax se incarca cuvantul de la adresa <DS:ESI>, ESI := ESI + 2
            mov dx, 0; punem cuvantul ax in dx:ax pentru a putea face impartirea la 10 fara a depasi dimensiunea
            
            ;facem o copie si aflam cate cifre are cuvantul 
            push dx 
            push ax
            pop ebx; copia cuvantului va fi in ebx
            push ecx 
            mov ecx, 0; numarul de cifre va fi memorat in ecx
            parcurgeNumar:
                div word[zece]; impartim la 10 numarul din registrul dx:ax; catul impartirii va fi in ax 
                inc ecx 
                cmp ax, 0 
                jz sfarsitParcurgeNumar 
                mov dx, 0; reasigura deimpartitul
                jmp parcurgeNumar; reluam bucla pana cand catul este 0
            sfarsitParcurgeNumar:
            
            push ebx 
            pop ax
            pop dx; preluam in dx:ax numarul din sir
            
            add edi, ecx;
            mov ebx, ecx; retinem cate cifre are numarul pentru a putea reveni la adresa de la care trebuie inserate urmatoarele cifre 
            
            ;urmeaza sa inseram cifrele numarului
            scoateCifre:
                div word[zece]; impartim la 10 numarul din registrul dx:ax si aflam ultima cifra; aceasta cifra se afla in dx
           
                mov cx, ax 
                mov ax, dx; mutam cifra din ax in dx
                stosb; la adresa <es:edi> se incarca octetul din al, adica cifra nou obtinuta
                mov ax, cx
                
                cmp ax, 0
                jz sfarsitScoateCifre; daca catul este 0 inseamna ca am obtinut toate cifrele si putem parasi bucla repetaSir 
                mov dx, 0; reasigura deimpartitul
                jmp scoateCifre; reluam bucla pentru obtinerea unei noi cifre
            sfarsitScoateCifre:
            pop ecx
            add edi, ebx; revenim la adresa la care urmeaza sa inseram cifrele urmatoarelor numere
        loop repetaSir; daca mai sunt elemente de parcurs (ecx>0) reia ciclul
        
        sfarsitSir: ;incheiem programul
            
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
