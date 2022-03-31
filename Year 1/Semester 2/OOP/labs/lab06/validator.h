//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#ifndef LAB06_VALIDATOR_H
#define LAB06_VALIDATOR_H

#include <cctype>
#include "domain.h"
#include "exceptions.h"


class Validator{
public:
    // validatori campuri
    // arunca InvalidFieldException daca valorile nu sunt valide
    static void validTitlu(const TypeTitlu &);
    static void validDescriere(const TypeDescriere &);
    static void validTip(const TypeTip &);
    static void validDurata(const TypeDurata&);

    // validator locatar
    // arunca ValidatorException continand fiecare eroare de validare a fiecarui camp
    static void validActivitate(const Activitate&);
};


#endif //LAB06_VALIDATOR_H
