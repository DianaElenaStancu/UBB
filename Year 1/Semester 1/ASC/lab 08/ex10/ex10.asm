;Sa se citeasca de la tastatura un nume de fisier si un text. Sa se creeze un fisier cu numele dat in directorul curent si sa se scrie textul in acel fisier. Observatii: Numele de fisier este de maxim 30 de caractere. Textul este de maxim 120 de caractere.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf, fopen, fclose, fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll    ; indicam asamblorului ca functia printf se gaseste in libraria msvcrt.dll
import scanf msvcrt.dll    ; similar pentru scanf
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier times 30 db 0
    text times 120 db 0
    litera db 0
    s1 dw 0
    s2 db 0
    message1 db "nume fisier: ", 0
    message2 db "textul pe care vrei sa il introduci in fisier: ", 0
    format db "%s", 0
    formatc db "%c", 0
    mod_acces db "a", 0          ; modul de deschidere a fisierului a - pentru adaugare                            
    descriptor_fis dd -1         ; variabila in care vom salva descriptorul fisierului - necesar pentru a putea face referire la fisier
    
; our code starts here
segment code use32 class=code
    start:
        ;apelam functia printf(message1)
        push dword message1; pe stiva se pune adresa stringului 
        call [printf]
        add esp, 4*1;eliberam parametrii de pe stiva
    
        ; vom apela functia scanf(format, nume_fisier)
        push dword nume_fisier 
        push dword format 
        call [scanf]
        add esp, 4*2 
        
        
        ;apelam functia printf(message2)
        push dword message2; pe stiva se pune adresa stringului 
        call [printf]
        add esp, 4*1;eliberam parametrii de pe stiva
    
        ;citim "in gol" enterul de la citirea anterioara
        push dword litera 
        push dword formatc
        call [scanf]
        
        mov edi, text
        citeste:
            ;apelam functia scanf(formatc, litera)
            push dword litera 
            push dword formatc
            call [scanf]
            add esp, 4*2 
            ;enter sau nl in codul ascii este 10, daca caracterul citit este enter inseamna ca am ajuns la sfarsitul sirului
            cmp byte [litera], 10 
            je sfarsit
            mov al, [litera] 
            stosb;adaugam in memorie litera cu litera, edi se incrementeaza automat cu 1 
            jmp citeste 
            
        sfarsit:
        mov al, 0
        stosb; punem 0 pentru a marca finalul sirului 
        
   
        ; apelam fopen pentru a crea fisierul
        ; functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ; eax = fopen(nume_fisier, mod_acces)
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; eliberam parametrii de pe stiva

        mov [descriptor_fis], eax   ; salvam valoarea returnata de fopen in variabila descriptor_fis
        
        ; verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        cmp eax, 0
        je final
        
        ; adaugam/scriem textul in fisierul deschis folosind functia fprintf
        ; fprintf(descriptor_fis, text)
        push dword text
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 4*2
        
        
        ; apelam functia fclose pentru a inchide fisierul
        ; fclose(descriptor_fis)
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
        
        
      final:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
