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
    Service& service;

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

    //lista activitati
    void lista_activitati(istream&, ostream&);

    //nuamra activitati
    void numara_activitati(istream & in, ostream & out);

    //undo
    void undo(ostream & out);
public:
    ConsoleUI()=delete;
    explicit ConsoleUI(Service& service) noexcept: service{service}{};
    // rulez meniul
    void run(istream& = cin, ostream& = cout);
    void run_file(ostream& = cout);
};


#endif //LAB06_UI_H