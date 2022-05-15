#include "IteratorColectie.h"
#include "Colectie.h"
//O(m)
void IteratorColectie::deplasare() {
    while ((curent < col.m) && col.e[curent].valoare == NIL)
        curent++;
}

IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* de adaugat */
    curent = 0;
    frecventa = 1;
    deplasare();
}

void IteratorColectie::prim() {
	/* de adaugat */
    curent = 0;
    frecventa = 1;
    deplasare();
}


void IteratorColectie::urmator() {
	/* de adaugat */
    if (frecventa  + 1 > col.e[curent].frecventa) {
        curent++;
        frecventa = 1;
        deplasare();
    } else {
        ++frecventa;
    }
}


bool IteratorColectie::valid() const {
	/* de adaugat */
	return curent < col.m;
}



TElem IteratorColectie::element() const {
	/* de adaugat */
	return col.e[curent].valoare;
}
