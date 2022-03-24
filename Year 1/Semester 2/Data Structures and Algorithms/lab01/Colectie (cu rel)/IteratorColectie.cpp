#include <iostream>
#include "IteratorColectie.h"
#include "Colectie.h"
using namespace std;

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* de adaugat */
    pozitie = 0;
    frecventa = 1;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
TElem IteratorColectie::element() const{
	/* de adaugat */
    if (this->valid()) {
        return col.e[pozitie].valoare;
    }
    else
        throw exception();
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
bool IteratorColectie::valid() const {
	/* de adaugat */
    return pozitie < col.n;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
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

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
void IteratorColectie::prim() {
	/* de adaugat */
    pozitie = 0;
    frecventa = 1;
}
