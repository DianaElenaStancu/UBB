#include <stdio.h>
/*
--cerinta
Sa se scrie un program C pentru unul dintre urmatoarele probleme.
Aplicatia ofera un mic meniu pentru a efectua repetat operatia ceruta.
Programul trebuie sa contina cel putin 2 functii. (functia main+ 1,2 functii)
Fiecare funtie trebuie specificata. Specificatia contine: a scurta descriere, descrierea parametrilor, conditii
impuse asupra datelor de intrare (preconditii), descriere rezultatului (post conditii)
--enunt
6. Tipareste triunghiul lui Pascal, cu toate combinarile C(m,k) de m obiecte
  luate cite k, k = 0, 1, ..., m, in linia m, pentru m = 1, 2, ..., n.
 */
int nCatek( int n, int k )
{
    /*
     * Calculeaza combinari de n luate cate k
     * n: tip intreg
     * k: tip intreg
     * preconditii: n, k numere naturale, n, k >= 0, n >= k
     * postconditii: numar natural semnificand numarul de combinari de n luate cate k
     */
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for (int i = 2; i <= k; ++i) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}
void tiparestePascal(int c) {
    /*
     * tipareste triunghiul lui Pascal
     * c: tip intreg
     * preconditii: c numar natural, c >= 0
     * postconditii: -
     */
    for (int n = 0; n <= c; n++) {
        for (int k = 0; k <= n; k++) {
            int comb = nCatek(n, k);
            printf("%d ", comb);
        }
        printf("\n");
    }
}
void menu() {
    int c;
    printf("Scrie un numar natural pentru a printa triunghiul lui Pascal sau -1 pentru a iesi din meniu \n");
    printf("n = ");
    scanf("%d", &c);

    while(c != -1){
        tiparestePascal(c);
        printf("n = ");
        scanf("%d", &c);
    }
    scanf("Bye!");
}
int main() {
    menu();
    return 0;
}

