#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
    return e1 <= e2;
}

/*
 * caz favorabil: perechea cautata se afla chiar in mijlocul vectorului - Θ(1)
 * caz defavorabil: perechea nu exista sau se afla intr-un capat al sirului - Θ(logn)
 * caz mediu: probabilitatea de a gasi un element dupa k cautari este p(k) = k/(1+2+...+log(n)) atunci
 *             T(n) =  Σ(i=1,n) p(i)*i = (2*log(n)+1)/3 e Θ(logn)
 * complexitate timp: O(logn)
 * complexitate spatiu: O(1)
 */
int Colectie::cautareBinara(Pereche *pereche, int stanga, int dreapta, TElem elem, bool& gasit) const{

    int mijloc = 0;
    while (stanga <= dreapta && !gasit) {
        mijloc = stanga + (dreapta - stanga) / 2;
        if (elem == pereche[mijloc].valoare) {
            gasit = true;
        }
        else {
            if (rel(elem, pereche[mijloc].valoare))
                dreapta = mijloc - 1;
            else
                stanga = mijloc + 1;
        }
    }
    if (rel(elem, pereche[mijloc].valoare))
        return mijloc;
    return mijloc + 1;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(n)
 * complexitate spatiu: O(n)
 */
void Colectie::redim() {
    //realocam un spatiu de capacitate dubla
    Pereche* eNou = new Pereche[2 * cp];
    //copiem vechile valori in eNou
    for (int i = 0; i < n; i++)
        eNou[i] = e[i];
    //dublam capacitatea
    cp = 2 * cp;
    //eliberam vechea zona
    delete[] e;
    //vectorul indica spre noua zona
    e = eNou;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
Colectie::Colectie() {
	/* de adaugat */
    //setam capacitatea
    this->cp = 1;
    //alocam spatiu de memorare pentru vector
    this->e = new Pereche[this->cp];
    //setam numarul de elemente (colectia este vida)
    this->n = 0;
}

/*
 * complexitatea realocarii este amortizata: Θ(1) (daca se considera n operatii de adaugare => redimensionarea se face cel
 * mult o data, n=dimensiunea vectorului)
 * caz favorabil: perechea trebuie adaugata/exista chiar in mijlocul vectorului- Θ(1)
 * caz defavorabil: perechea (nu) exista in vector si se trebuie adaugata/se afla intr-un capat al sirului - Θ(logn)
 * caz mediu: probabilitatea de a gasi un element dupa k cautari este p(k) = k/(1+2+...+log(n)) atunci
 *             T(n) =  Σ(i=1,n) p(i)*i = (2*log(n)+1)/3 e Θ(logn)
 * complexitate timp: O(logn)
 * complexitate spatiu: O(1)
 */
void Colectie::adauga(TElem e) {
	/* de adaugat */
    if (n == 0) {
        Pereche p;
        p.valoare = e;
        p.frecventa = 1;
        this->e[0] = p;
        n++;
        return;
    }
    bool gasit = false;
    int poz = cautareBinara(this->e, 0, n - 1, e, gasit);
    if (gasit)
        this->e[poz].frecventa++;
    else {
        if (n == cp)
            redim();
        for (int i = n; i > poz; i--)
            this->e[i] = this->e[i - 1];
        Pereche p;
        p.valoare = e;
        p.frecventa = 1;
        this->e[poz] = p;
        n++;
    }
}

/*
 * caz favorabil: perechea exista chiar in mijlocul vectorului- Θ(1)
 * caz defavorabil: perechea (nu) exista in vector si trebuie stearsa/se afla intr-un capat al sirului - Θ(logn)
 * caz mediu: probabilitatea de a gasi un element dupa k cautari este p(k) = k/(1+2+...+log(n)) atunci
 *             T(n) =  Σ(i=1,n) p(i)*i = (2*log(n)+1)/3 e Θ(logn)
 * complexitate timp: O(logn)
 * complexitate spatiu: O(1)
 */
bool Colectie::sterge(TElem e) {
	/* de adaugat */
    bool gasit = false;
    int poz = cautareBinara(this->e, 0, n - 1, e, gasit);
    if (!gasit)
        return false;
    if (this->e[poz].frecventa > 1)
        this->e[poz].frecventa--;//stergem o singura aparitie a elementului e
    else {
        for (int i = poz; i < n-1; i++)
            this->e[i] = this->e[i + 1];
        n--;
    }
    return true;
}

/*
 * caz favorabil: perechea cautata se afla chiar in mijlocul vectorului - Θ(1)
 * caz defavorabil: perechea nu exista sau se afla intr-un capat al sirului - Θ(logn)
 * caz mediu: probabilitatea de a gasi un element dupa k cautari este p(k) = k/(1+2+...+log(n)) atunci
 *             T(n) =  Σ(i=1,n) p(i)*i = (2*log(n)+1)/3 e Θ(logn)
 * complexitate timp: O(logn)
 * complexitate spatiu: O(1)
 */
bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
    bool gasit = false;
    cautareBinara(this->e, 0, n - 1, elem, gasit);
    return gasit;
}

/*
 * caz favorabil: perechea cautata se afla chiar in mijlocul vectorului - Θ(1)
 * caz defavorabil: perechea nu exista sau se afla intr-un capat al sirului - Θ(logn)
 * caz mediu: probabilitatea de a gasi un element dupa k cautari este p(k) = k/(1+2+...+log(n)) atunci
 *             T(n) =  Σ(i=1,n) p(i)*i = (2*log(n)+1)/3 e Θ(logn)
 * complexitate timp: O(logn)
 * complexitate spatiu: O(1)
 */
int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
    bool gasit = false;
    int poz = cautareBinara(this->e, 0, n - 1, elem, gasit);
    if (!gasit)
        return 0;
    return this->e[poz].frecventa;
}


/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
int Colectie::dim() const {
	/* de adaugat */
    int d = 0;
    for (int i = 0; i < n; i++)
        d += this->e[i].frecventa;
	return d;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
bool Colectie::vida() const {
	/* de adaugat */
    return n == 0;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
Colectie::~Colectie() {
	/* de adaugat */
    delete[] e;
}
