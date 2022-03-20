#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	/* de adaugat */
    primul = NULL;
    ultimul = NULL;
}


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


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
    Nod *p = primul;
    while (p != NULL && p->valoare != elem)
        p = p -> urmator;
    if (p == NULL)
        return false;
    return true;
}


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

bool Multime::vida() const {
	/* de adaugat */
	return dim() == 0;
}


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

