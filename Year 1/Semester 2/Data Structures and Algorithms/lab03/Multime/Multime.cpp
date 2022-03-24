#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
Multime::Multime() {
	/* de adaugat */
    primul = NULL;
    ultimul = NULL;
}

/*
 * caz favorabil: lista este goala Θ(1)
 * caz defavorabil: elementul trebuie adaugat pe ultima pozitie Θ(n)
 * caz mediu: probabilitatea de a trebui sa adaugam in orice pozitie este 1/(n+1)
 *            T(n) = 1/(n+1)*Σ(i=1,n+1)i=(n+1)(n+2)/((n+1)*2) = (n+2)/2 e Θ(n)
 * complexitate timp: O(n)
 * complexitate spatiu: O(1)
 */
bool Multime::adauga(TElem elem) {
	/* de adaugat */
    if (primul == NULL) {
        Nod* p = new Nod;
        p->valoare = elem;
        p->urmator = NULL;
        this->primul = this->ultimul = p;
        return true;
    }
    if (cauta(elem))
        return false;
    Nod* p = new Nod;
    p->valoare = elem;
    p->urmator = NULL;
    ultimul->urmator = p;
    ultimul = p;
	return true;
}

/*
 * caz favorabil: lista este goala Θ(1)
 * caz defavorabil: elementul trebuie adaugat pe ultima pozitie Θ(n)
 * caz mediu: probabilitatea de a trebui sa stergem in orice pozitie este 1/(n+1)
 *            T(n) = 1/(n+1)*Σ(i=1,n+1)i=(n+1)(n+2)/((n+1)*2) = (n+2)/2 e Θ(n)
 * complexitate timp: O(n)
 * complexitate spatiu: O(1)
 */
bool Multime::sterge(TElem elem) {
	/* de adaugat */
    if (!cauta(elem))
        return false;
    Nod *p = primul;
    if (p->valoare == elem) {
        primul = primul->urmator;
        return 1;
    }
    while (p->urmator != NULL && p->urmator->valoare != elem)
        p = p->urmator;
    if (p == ultimul) {
        p->urmator = NULL;
        ultimul = p;
        return true;
    }
    p->urmator = p->urmator->urmator;
	return true;
}

/*
 * caz favorabil: lista este goala sau elementul cautat se afla pe prima pozitie Θ(1)
 * caz defavorabil: elementul cautat se afla pe ultima pozitie sau nu exista Θ(n)
 * caz mediu: probabilitatea de a exista elementul in orice pozitie este 1/(n+1)
 *            T(n) = 1/(n+1)*Σ(i=1,n+1)i=(n+1)(n+2)/((n+1)*2) = (n+2)/2 e Θ(n)
 * complexitate timp: O(n)
 * complexitate spatiu: O(1)
 */
bool Multime::cauta(TElem elem) const {
	/* de adaugat */
    Nod *p = primul;
    while (p != NULL && p->valoare != elem)
        p = p -> urmator;
    if (p == NULL)
        return false;
    return true;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(n)
 * complexitate spatiu: Θ(1)
 */
int Multime::dim() const {
	/* de adaugat */
    int n = 0;
    Nod* p = primul;
    while (p != NULL) {
        ++n;
        p = p->urmator;
    }
	return n;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(n)
 * complexitate spatiu: Θ(1)
 */
bool Multime::vida() const {
	/* de adaugat */
	return dim() == 0;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(n)
 * complexitate spatiu: Θ(1)
 */
void destroy(Nod *p) {
    if (p == NULL)
        return;
    destroy(p->urmator);
    delete p;
    p = NULL;
}

Multime::~Multime() {
	/* de adaugat */
    destroy(this->primul);
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

