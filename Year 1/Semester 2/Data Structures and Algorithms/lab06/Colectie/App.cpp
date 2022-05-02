#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
#include "Colectie.h"
using namespace std;
void t() {
    Colectie c;
    assert(c.vida() == true);
    assert(c.dim() == 0); //adaug niste elemente
    c.adauga(5);
    c.adauga(15);
    c.adauga(20);
    c.adauga(35);
    c.adauga(30);
    assert(c.cauta(5));
    assert(c.cauta(15));
    assert(c.cauta(20));
    assert(c.cauta(35));
    assert(c.cauta(30));
    assert(c.sterge(20));
    assert(c.cauta(5));
    assert(c.cauta(15));
    assert(c.cauta(20)==false);
    assert(c.cauta(35));
    assert(c.cauta(30));
    assert(c.sterge(5));
    assert(c.cauta(5)==false);
    assert(c.cauta(15));
    assert(c.cauta(20)==false);
    assert(c.cauta(35));
    assert(c.cauta(30));
    assert(c.sterge(15));
    assert(c.cauta(5)==false);
    assert(c.cauta(15)==false);
    assert(c.cauta(20)==false);
    assert(c.cauta(35));
    assert(c.cauta(30));
    assert(c.sterge(30));
    assert(c.cauta(5)==false);
    assert(c.cauta(15)==false);
    assert(c.cauta(20)==false);
    assert(c.cauta(35));
    assert(c.cauta(30)==false);
    assert(c.sterge(35));
    assert(c.cauta(5)==false);
    assert(c.cauta(15)==false);
    assert(c.cauta(20)==false);
    assert(c.cauta(35)==false);
    assert(c.cauta(30)==false);
}

int main() {
	testAll();
	testAllExtins();
	cout<<"End";
}
