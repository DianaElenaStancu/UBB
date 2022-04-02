#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <iostream>
using namespace std;

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	/* de adaugat */
    curent = d.prim;
}


void IteratorDictionar::prim() {
	/* de adaugat */
    curent = dict.prim;
}


void IteratorDictionar::urmator() {
	/* de adaugat */
    curent = dict.urm[curent];

}


TElem IteratorDictionar::element() const{
	/* de adaugat */

	return pair <TCheie, TValoare>  (dict.elems[curent].first, dict.elems[curent].second);
}


bool IteratorDictionar::valid() const {
	/* de adaugat */
	return curent != -1;
}

