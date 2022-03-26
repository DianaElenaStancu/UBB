
#include "TestExtins.h"
#include "TestScurt.h"
#include <iostream>
#include "Multime.h"
#include "IteratorMultime.h"
using namespace std;
void testDif() {
    Multime m;
    assert(m.vida() == true);
    assert(m.dim() == 0);
    assert(m.diferentaMaxMin() == -1);
    assert(m.adauga(5)==true);
    assert(m.diferentaMaxMin() == 0);
    assert(m.adauga(1)==true);
    assert(m.diferentaMaxMin() == 4);
    assert(m.adauga(10)==true);
    assert(m.diferentaMaxMin() == 9);
    assert(m.adauga(7)==true);
    assert(m.diferentaMaxMin() == 9);
    assert(m.adauga(-3)==true);
    assert(m.diferentaMaxMin() == 13);
}
int main() {

    testDif();

    cout << "testDif passed :)\n";

	testAll();
	testAllExtins();

	cout << "That's all!" << endl;


}
