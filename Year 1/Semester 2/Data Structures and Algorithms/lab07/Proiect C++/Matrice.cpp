#include "Matrice.h"
#include <exception>
#include <stack>
using namespace std;


/*
  theta(2 * capacitate)
*/
void Matrice::redimensioneaza()
{
    // realocare vectori (redimensionare + copiere elemente)
    Triplet* nouE = new Triplet[capacitate * 2];
    int* nouStanga = new int[capacitate * 2];
    int* nouDreapta = new int[capacitate * 2];
    for (int i = 0; i < capacitate; i++) {
        nouE[i] = e[i];
        nouStanga[i] = stanga[i];
        nouDreapta[i] = dreapta[i];
    }
    delete[] dreapta;
    delete[] stanga;
    delete[] e;
    e = nouE;
    stanga = nouStanga;
    dreapta = nouDreapta;
    // redimensionarea spatiului liber
    for (int i = capacitate; i <= 2 * capacitate - 2; i++)
        stanga[i] = i + 1;
    stanga[2 * capacitate - 1] = -1;
    primLiber = capacitate;
    capacitate = capacitate * 2;
}


/*
  theta(1)
*/
int Matrice::aloca()
{
    //se sterge primul element din lista spatiului liber
    int i = primLiber;
    primLiber = stanga[primLiber];
    return i;
}


/*
  theta(1) (daca nu se face redimensionare)
*/
int Matrice::creeazaNod(int l, int c, TElem elem)
{
    if (primLiber == -1 && radacina != -1)
        redimensioneaza();
    int i = aloca();
    e[i].valoare = elem;
    e[i].linie = l;
    e[i].coloana = c;
    stanga[i] = -1;
    dreapta[i] = -1;
    return i;
}


/*
  theta(1)
*/
Matrice::Matrice(int m, int n) {
    if (m <= 0 || n <= 0)
        throw exception();
    linii = m;
    coloane = n;
    capacitate = 10;
    e = new Triplet[capacitate];
    stanga = new int[capacitate];
    dreapta = new int[capacitate];
    radacina = -1;

    //se initializeaza lista spatiului liber
    for (int i = 0; i < capacitate - 1; i++) {
        stanga[i] = i + 1;
    }
    for (int i = capacitate - 2; i >= 0; i--) {
        dreapta[i + 1] = i;
    }
    stanga[capacitate - 1] = -1;
    primLiber = 0;
}


/*
  theta(1)
*/
int Matrice::nrLinii() const {
    return linii;
}


/*
  theta(1)
*/
int Matrice::nrColoane() const {
    return coloane;
}


/*
  CF : theta(1) -> elementul cautat este chiar radacina
  CD : theta(n) -> arborele este degenerat si elementul cautat este cel de pe ultimul nivel
  CM : theta(h)
*/
TElem Matrice::element(int i, int j) const {

    if (i < 0 || i >= linii || j < 0 || j >= coloane)
        throw exception();

    int aux = radacina;
    while (aux != -1) {
        if (e[aux].linie == i && e[aux].coloana == j)
            return e[aux].valoare;

        if (e[aux].linie < i || (e[aux].linie == i && e[aux].coloana < j))
            aux = dreapta[aux];

        else
            aux = stanga[aux];
    }

    return NULL_TELEMENT;
}


/*
  CF : theta(1) -> elementul de modificat este chiar radacina
  CD : theta(n) -> arborele este degenerat si elementul de modificat este cel de pe ultimul nivel
  CM : theta(h)
*/
TElem Matrice::modifica(int i, int j, TElem elem) {

    if (i < 0 || i >= linii || j < 0 || j >= coloane)
        throw exception();

    if (radacina == -1) {	// se adauga radacina
        int nou = creeazaNod(i, j, elem);
        radacina = nou;
        return NULL_TELEMENT;
    }

    int aux = radacina;
    int parinte = -1;

    while (aux != -1 && !(e[aux].linie == i && e[aux].coloana == j)) {
        if (e[aux].linie < i || (e[aux].linie == i && e[aux].coloana < j)) {  // caut in subarborele drept
            parinte = aux;
            aux = dreapta[aux];
        }
        else {
            parinte = aux;
            aux = stanga[aux];
        }
    }

    if (e[aux].linie == i && e[aux].coloana == j) {	  // s-a gasit elementul cautat; se modifica valoarea sa
        auto valoareaVeche = e[aux].valoare;
        e[aux].valoare = elem;
        return valoareaVeche;
    }

    else {	// se adauga un nou element si se returneaza valoarea veche - NULL_TELEMENT
        int nou = creeazaNod(i, j, elem);

        if (i < e[parinte].linie || (i == e[parinte].linie && j < e[parinte].coloana))
            stanga[parinte] = nou;    // noul nod va fi fiul stang al precedentului

        else dreapta[parinte] = nou;   // noul nod va fi fiul drept al precedentului
    }

    return NULL_TELEMENT;
}


/*
    subalgoritm valoareMaxima()
        max = 0
        Pentru i <- 0, nrLinii()-1 executa
            Pentru j <- 0, nrColoanre()-1 executs
                Daca max < element(i, j) atunci
                    max <- element(i, j)
        valoareMaxima() <- max

*/
int Matrice::valoareMaxima() const{
    int i,j, max = 0;
    for (i = 0; i < nrLinii(); i++)
        for (j = 0; j < nrColoane(); j++)
            if (max < element(i, j))
                max = element(i, j);
    return max;
};