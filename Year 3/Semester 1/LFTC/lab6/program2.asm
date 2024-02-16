bits 32
global start

extern exit
import exit msvcrt.dll
extern scanf
import scanf msvcrt.dll
extern printf
import printf msvcrt.dll

segment data use32 class=data
	format db "%d", 0
	 a times 4 db 0 
	 temp1 times 4 db 0 
	 temp2 times 4 db 0 
	 temp3 times 4 db 0 
	 temp4 times 4 db 0 
	 temp5 times 4 db 0 

segment code use32 class=code
	start:
		push dword a 
		push dword format 
		call [scanf] 
		add ESP, 4 * 2 



		mov al, 3 
		mov ah, 0 
		mov dl, [a] 
		mul dl 
		mov [temp1], al 

		mov al, 2 
		add al, [temp1] 
		mov [temp2], al 


		mov al, [temp2] 
		add al, 3 
		mov [temp3], al 



		mov al, 4 
		mov ah, 0 
		mov dl, 2 
		div dl 
		mov [temp4], al 

		mov al, [temp3] 
		sub al, [temp4] 
		mov [temp5], al 
		mov al, [temp5]
		mov [a], al

		push dword [a] 
		push dword format 
		call [printf] 
		add ESP, 4 * 2 

		push dword 0
		call [exit]