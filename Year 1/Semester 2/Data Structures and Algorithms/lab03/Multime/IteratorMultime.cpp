#include <iostream>
#include "IteratorMultime.h"
#include "Multime.h"

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: 0(1)
 * complexitate spatiu: 0(1)
 */
IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	/* de adaugat */
    this->prim();
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: 0(1)
 * complexitate spatiu: 0(1)
 */
void IteratorMultime::prim() {
	/* de adaugat */
    p = multime.primul;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: 0(1)
 * complexitate spatiu: 0(1)
 */
void IteratorMultime::urmator() {
	/* de adaugat */
    if (!this->valid())
        throw std::exception();
    p = p -> urmator;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: 0(1)
 * complexitate spatiu: 0(1)
 */
TElem IteratorMultime::element() const {
	/* de adaugat */
    if (this->valid())
        return p->valoare;
    throw std::exception();
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: 0(1)
 * complexitate spatiu: 0(1)
 */
bool IteratorMultime::valid() const {
	/* de adaugat */
	return p != NULL;
}
