#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

using namespace std;
void test() {
    Matrice m(10, 10);
    assert(m.valoareMaxima() == 0);

    for (int j = 0; j < m.nrColoane(); j++)
        m.modifica(4, j, j);
    assert(m.valoareMaxima() == 9);

    m.modifica(4, 2, 400);
    assert(m.valoareMaxima() == 400);

    m.modifica(1, 0, 7675);
    m.modifica(1, 9, 1230);
    assert(m.valoareMaxima() == 7675);
}

int main() {

	testAll();
	testAllExtins();
    test();
	cout<<"End";
}
