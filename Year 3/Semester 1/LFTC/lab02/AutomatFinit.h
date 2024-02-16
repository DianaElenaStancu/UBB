//
// Created by Diana Stancu on 11/13/2023.
//

#ifndef AUTOMAT_SI_ANALIZATOR_LEXICAL_AUTOMATFINIT_H
#define AUTOMAT_SI_ANALIZATOR_LEXICAL_AUTOMATFINIT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

class AutomatFinit {
public:
    AutomatFinit(ifstream& fin);
    int findPrefixMaximal(string text);
private:
    struct tranzitie {
        string stare_initiala;
        string stare_finala;
        char valoare;
    };

    vector<tranzitie> tranzitii;
    vector<string> multime_stari;
    vector<string>multime_stari_finale;
    string stare_initiala;
    int numar_tranzitii;
    set<char>alfabet;
};


#endif //AUTOMAT_SI_ANALIZATOR_LEXICAL_AUTOMATFINIT_H
