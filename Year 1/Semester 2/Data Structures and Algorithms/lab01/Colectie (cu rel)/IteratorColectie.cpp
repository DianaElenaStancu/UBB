#include <iostream>
#include "IteratorColectie.h"
#include "Colectie.h"
using namespace std;

IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* de adaugat */
    pc = 0;
}

TElem IteratorColectie::element() const{
	/* de adaugat */
    if (!valid())
        throw exception();
    else
        return col.element[pc];
	return -1;
}

bool IteratorColectie::valid() const {
	/* de adaugat */
    if (pc < col.dim())
        return true;
	return false;
}

void IteratorColectie::urmator() {
	/* de adaugat */
    if (!valid())
        throw exception();
    pc++;
}

void IteratorColectie::prim() {
	/* de adaugat */
    pc = 0;
}
