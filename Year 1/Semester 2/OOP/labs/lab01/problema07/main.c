#include <stdio.h>
/*
 *9. Citeste un sir de numere naturale nenule terminat cu 0 si determina

    numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
 */



int prelucrare_sir(){
    /*
     * functia citeste fiecare element al produsului si calculeaza cati
     * de 10, 2, respectiv 5 are in descompunerea sa
     * in final se vor lua in considerare toate perechile (5,2) care in urma produsului dintre cele doua
     * si factorii de 10
     * preconditii: c numar natural diferit de 0
     * postconditii: rezultatul numar natural >= 0
     */
    int c, zece, doi, cinci, rez;
    zece = doi = cinci = 0;
    scanf("%d", &c);

    while(c != 0) {
        //prelucrare numar
        while(c%10 == 0) {
            c /= 10;
            ++zece;
        }
        while(c%2 == 0) {
            c /= 2;
            ++doi;
        }
        while(c%5 == 0) {
            c /= 5;
            ++cinci;
        }
        scanf("%d", &c);
    }
    rez = zece;
    if (cinci < doi)
        rez += cinci;
    else
        rez += doi;
    return rez;
}
void menu() {
    /*
     * meniul problemei
     * prezinta enuntul si afiseaza rezultatul cerut
     */
    printf("Scrie un sir de numere naturale nenule terminat cu 0 \n");
    printf("sir = ");
    int rez = prelucrare_sir();
    printf("Produsul va avea %d zerouri", rez);
    scanf("Bye!");
}
int main() {
    menu();
    return 0;
}
