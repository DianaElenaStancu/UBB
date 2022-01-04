;Se da un numar in baza 2 reprezentat pe 32 de biti. Sa se afiseze reprezentarea in baza 16. (se foloseste conversia rapida)
;exemplu: 11_0100_1010_1110_0000_0110_0010_1111b
;programul afiseaza: numarul in hexazecimal este 34AE062Fh
bits  32
global  start
extern  printf, exit, conversie, inverseaza 
import  printf msvcrt.dll
import  exit msvcrt.dll
segment  data use32 class=data
	nrBinar dd 11_0100_1010_1110_0000_0110_0010_1111b
    mesaj db "numarul in hexazecimal este %sh", 0
    nrHexa times 32 db 0
    
segment  code use32 class=code
;  programul "principal"       
start:
    ;calculeaza
	push dword nrHexa        ; se salveaza pe stiva adresa la care se va memora numarul in hexa
    push dword [nrBinar]     ; se salveaza pe stiva numarul in format binar
	call conversie      ; apel procedura conversie - parametrii transmisi prin stiva

    ;inverseaza 
    push dword nrHexa       ; se salveaza pe stiva adresa la care este memorat numarul in hexa
    call inverseaza     ; apel procedura inverseaza - parametrul transmis prin stiva, unul prin registrul edi
    
        
    ;afisare
    push dword nrHexa 
    push dword mesaj
    call [printf]
	call [exit]