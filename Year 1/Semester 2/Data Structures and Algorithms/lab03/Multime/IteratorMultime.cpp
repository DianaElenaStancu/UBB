#include <iostream>
#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	/* de adaugat */
    this->prim();
}


void IteratorMultime::prim() {
	/* de adaugat */
    p = multime.primul;
}


void IteratorMultime::urmator() {
	/* de adaugat */
    if (!this->valid())
        throw std::exception();
    p = p -> urmator;
}


TElem IteratorMultime::element() const {
	/* de adaugat */
    if (this->valid())
        return p->valoare;
    throw std::exception();
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	return p != NULL;
}
