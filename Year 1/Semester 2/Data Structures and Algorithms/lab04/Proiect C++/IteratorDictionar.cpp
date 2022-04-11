#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>
using namespace std;

IteratorDictionar::IteratorDictionar(Dictionar& d) : dict(d){
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

	return  make_pair(dict.elems[curent].first, dict.elems[curent].second);
}


bool IteratorDictionar::valid() const {
	/* de adaugat */
	return curent != -1;
}

/*
 * complexitate timp: O(n)
 *
 *Functie elimina() {
 *  pre: Dictionar d - un dictionar IteratorDictionar iterator al unui dictionar
 *  post: arunca o exceptie daca iteraratorul nu este valid
 *        returneaza elementul de pe pozitia redata de iterator, dupa eliminarea elementului curent; element e TElem
 *  @ - exceptii aruncate
 *
 *  Daca valid(it) <- false atunci
 *      @
 *  SfDaca
 *
 *  eliminat <- element(it)
 *  urmator(it)
 *  sterge(d, eliminat)
 *  elimina() <- eliminat
 *}
 */
TElem IteratorDictionar::elimina() {
    if (!valid()) {
        //iteratorul este invalid si aruncam o exceptie
        throw exception();
    }
    //daca iteratorul este valid eliminam elementul de pe pozitia curenta
    //trecem la urmatorul element
    TElem eliminat = element();
    urmator();
    dict.sterge(eliminat.first);
    return eliminat;
}

