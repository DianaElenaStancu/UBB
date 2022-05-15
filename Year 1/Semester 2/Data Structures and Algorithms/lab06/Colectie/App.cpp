#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
#include "Colectie.h"
using namespace std;
void t() {
    Colectie c;
    c.adauga(5);
    c.adauga(15);
    c.adauga(20);
    c.adauga(35);
    c.adauga(30);
    Colectie b;
    c.adaugaToateElementele(b);
    assert(c.dim() == 5);
    b.adauga(6);
    b.adauga(15);
    b.adauga(15);
    b.adauga(20);
    b.adauga(35);
    b.adauga(30);
    c.adaugaToateElementele(b);
    assert(c.nrAparitii(5) == 1);
    assert(c.nrAparitii(15) == 3);
    assert(c.nrAparitii(20) == 2);
    assert(c.nrAparitii(35) == 2);
    assert(c.nrAparitii(30) == 2);
}

int main() {
    t();
	testAll();
	testAllExtins();
	cout<<"End";
}
