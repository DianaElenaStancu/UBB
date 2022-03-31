//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#ifndef LAB06_UI_H
#define LAB06_UI_H

#include "service.h"
#include <iostream>
using std::cin;
using std::cout;

class ConsoleUI
{
private:
    Service service;

//    // afisarea meniului
//    void printMenu(ostream&);

    // citeste datele unui locatar
    // le atribui parametrilor de tip out
//    void readActivitate(istream&, ostream&, TypeTitlu&, TypeDescriere&, TypeTip&, TypeDurata&);

    // afisez locatarul
//    void writeActivitate(ostream&, const Activitate&);

    // adauga
    void adauga(istream&, ostream&);

    // sterge
    void sterge(istream&, ostream&);

    // modifica
    void modifica(istream&, ostream&);

    // listare
    void afisare(ostream&);

    // cauta apartament
    void cauta(istream&, ostream&);

    // filtrare
    void filtrare(istream&, ostream&);

    // sortare
    void sortare(istream&, ostream&);

public:
    ConsoleUI()=default;
    // rulez meniul
    void run(istream& = cin, ostream& = cout);
};


#endif //LAB06_UI_H
