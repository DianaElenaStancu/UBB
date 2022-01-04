#include <stdio.h>
#include <string.h>

void conversie(int nrBinar, char nrHexa[]);
void inverseaza(int len, char nrHexa[]);
int main()
{
    //int a = 0b1101;//0b110100101011100000011000101111; = 34AE062Fh
    int nrBinar = 0b110100101011100000011000101111;
    char nrHexa[10] = "";
    printf("Numarul care trebuie convertit %d!\n", nrBinar);
    conversie(nrBinar, nrHexa);
    inverseaza(strlen(nrHexa), nrHexa);
    printf("Numarul in hexazecimal este: %sh", nrHexa);
	return 0;
}