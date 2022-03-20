#include <iostream>
#include "IteratorColectie.h"
#include "Colectie.h"
using namespace std;

IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* de adaugat */
    pozitie = 0;
    frecventa = 1;
}

TElem IteratorColectie::element() const{
	/* de adaugat */
    if (this->valid()) {
        return col.e[pozitie].valoare;
    }
    else
        throw exception();
}

bool IteratorColectie::valid() const {
	/* de adaugat */
    return pozitie < col.n;
}

void IteratorColectie::urmator() {
	/* de adaugat */
    if (this->valid())
        if (frecventa < col.e[pozitie].frecventa)
            frecventa++;
        else {
            pozitie++;
            frecventa = 1;
        }
    else
        throw exception();
}

void IteratorColectie::prim() {
	/* de adaugat */
    pozitie = 0;
    frecventa = 1;
}
