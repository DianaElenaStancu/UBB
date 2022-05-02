#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

//functia care da <hashCode>-ul unui element
int hashCode(TElem el){
//ptr moment numarul e intreg
    return abs(el);
}

//functia de dispersie
int Colectie::d(TElem el) const {
    //dispersia prin diviziune
    return hashCode(el) % m;
}

Colectie::Colectie() {
	/* de adaugat */
    m = MAX; //initializam m cu o valoare predefinita
    //daca va fi cazul, se poate redimensiona tabela si sa se redisperseze elementele
    //se initializeaza vectorii
    for (int i = 0; i < m; i++) {
        e[i].valoare = NIL; // consideram ca elementul e intreg
        e[i].frecventa = 0;
        urm[i] = -1;
    }
    //initializare primLIber
    primLiber = 0;
    size = 0;
}

// actualizare primLiber
void Colectie::actPrimLiber()
{
    primLiber++;
    while (primLiber < m && e[primLiber].valoare != NIL)
        primLiber++;
}

void Colectie::adauga(TElem elem) {
	/* de adaugat */
    ++size;
    //locatia de dispersie a cheii
    int i=d(elem);
    if (e[i].valoare == NIL)	// pozitia este libera
    {
        e[i].valoare = elem;	// adaugam elementul
        e[i].frecventa = 1;
        if (i == primLiber)
            actPrimLiber();	// actualizam primLiber, daca este nevoie
        return;
    }
    int j = -1;	// j va retine pozitia precedenta lui i, pentru a putea reface inlantuirea
    // daca pozitia nu este libera
    while (i != -1)	// iteram pana gasim capatul inlantuirii
    {
        //verificam daca elementul exista deja in tabela
        if (e[i].valoare == elem) {
            e[i].frecventa++;
            return;
        }
        j = i;
        i = urm[i];
    }
    if (primLiber >= m) {
        cout << "Depasire!";
        return;
    }


    // adaugam elementul
    e[primLiber].valoare = elem;
    e[primLiber].frecventa = 1;
    urm[j] = primLiber;
    actPrimLiber();
}


bool Colectie::sterge(TElem elem) {
	/* de adaugat */
    /*int i=d(elem);
    if (e[i].valoare == NIL)
        return false;
    int j = -1;
    while (i != -1)
    {
        //verificam daca elementul exista deja in tabela
        if (e[i].valoare == elem) {
            if (e[i].frecventa > 1) {
                --e[i].frecventa;
            } else {
                if (j != -1) urm[j] = urm[i];
                e[i].valoare = NIL;
                e[i].frecventa = 0;
                urm[i] = -1;
                if (primLiber > i)primLiber = i;
            }
            size--;
            return true;
        }
        j = i;
        i = urm[i];
    }
	return false;*/
    int i = d(elem);
    int j = -1;
    int k = 0;
    while (urm[k] != i && k < m)
        k++;
    if (k != m)
        j = k;
    while (i != -1 && e[i].valoare != elem) {
        j = i;
        i = urm[i];
    }
    if (i == -1)
        return false;

    if (e[i].frecventa > 1) {
        --e[i].frecventa;
    } else {
        bool found = false;
        do {
            int p = urm[i];
            int pp = i;
            while (p != -1 && d(e[p].valoare) != i) {
                pp = p;
                p = urm[p];
            }
            if (p == -1)
                found = true;
            else {
                e[i] = e[p];
                i = p;
                j = pp;
            }
        } while (!found);
        if (j != -1)
            urm[j] = urm[i];
        urm[i] = -1;
        e[i] = { NIL, 0 };
        if (primLiber > i)
            primLiber = i;
    }
    size--;
    return true;
}


bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
    int i=d(elem);
    if (e[i].valoare == NIL)
        return false;
    while (i != -1)	// iteram pana gasim capatul inlantuirii
    {
        //verificam daca elementul exista deja in tabela
        if (e[i].valoare == elem) {
            return true;
        }
        i = urm[i];
    }
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
    int i=d(elem);
    if (e[i].valoare == NIL)
        return 0;
    while (i != -1)
    {
        //verificam daca elementul exista deja in tabela
        if (e[i].valoare == elem) {
            return e[i].frecventa;
        }
        i = urm[i];
    }
	return 0;
}


int Colectie::dim() const {
	return size;
}


bool Colectie::vida() const {
	/* de adaugat */
	return size==0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
}


