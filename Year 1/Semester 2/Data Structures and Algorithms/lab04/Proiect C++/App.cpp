#include "TestExtins.h"
#include "TestScurt.h"
#include <iostream>
#include "Dictionar.h"
#include "IteratorDictionar.h"
using namespace std;
void testEliminaIterator() {
    //creem un dictionar si un iterator
    Dictionar d;
    IteratorDictionar id = d.iterator();
    //incercam sa eliminam element cand iteratorul este doar creat
    try {
       id.elimina();
       assert(false);
    } catch(...) {
       assert(true);
    }

    //eliminam primul element si vedem daca iteratorul este invalid
    d.adauga(5, 11);
    id.prim();
    assert(id.elimina() == make_pair(5, 11));
    assert(id.valid() == false);
    assert(d.dim() == 0);

    //eliminam un element din mijloc si verificam daca pointeaza spre urmatorul element
    d.adauga(1, 10);
    d.adauga(2, 12);
    d.adauga(3, 14);
    id.prim();
    assert(id.elimina() == make_pair(3, 14));
    assert(id.valid());
    assert(id.element() == make_pair(2, 12));

    //eliminam ultimul element
    assert(id.elimina() == make_pair(2, 12));
    assert(id.valid());
    assert(id.element() == make_pair(1, 10));
    assert(id.elimina() == make_pair(1, 10));
    assert(id.valid() == false);
    assert(d.dim() == 0);
}
int main() {
	testAll();
	testAllExtins();
    testEliminaIterator();
	cout << "That's all!" << endl;
	return 0;
}

