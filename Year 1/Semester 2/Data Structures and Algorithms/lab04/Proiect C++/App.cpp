#include "TestExtins.h"
#include "TestScurt.h"
#include "Dictionar.h"
#include <iostream>
using namespace std;
void myTest() {
    Dictionar d;
    for (int i = -10; i <= 10; i = i + 2) { //adaugam elemente din 2 in 2
        d.adauga(i,i);
    }
    for (int i = 10; i > -10; i--) { //stergem descrescator (in ordine inversa fata de ordinea adaugarii)
        if (i % 2 == 0) {
            assert(d.sterge(i) == i);
        }
        else {
            assert(d.sterge(i) == NULL_TVALOARE);
        }
    }

    assert(d.dim() == 1);
    //printD(d);

    d.sterge(-10);
    assert(d.dim() == 0);
    cout << "----------------\n";
    for (int i = -10; i < 10; i++) { //adaugam de 5 ori pe fiecare element
        d.adauga(i,0);
        d.adauga(i,1);
        d.adauga(i,2);
        d.adauga(i,3);
        d.adauga(i,4);
    }
    //printD(d);
    assert(d.dim() == 20);
    for (int i = -20; i < 20; i++) { //stergem elemente inexistente si existente
        if (i < -10 || i >= 10) {
            assert(d.sterge(i) == NULL_TVALOARE);
        }
        else {
            assert(d.sterge(i) == 4);
            assert(d.sterge(i) == NULL_TVALOARE);
        }
    }
}

int main() {
	testAll();
	//testAllExtins();
    //myTest();

	cout << "That's all!" << endl;
	return 0;
}

