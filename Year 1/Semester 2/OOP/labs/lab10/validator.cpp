//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#include "validator.h"


void Validator::validTitlu(const TypeTitlu & titlu) {
    if (titlu.empty() == 1)
        throw InvalidFieldException("Titlul nu este valid!\n");
    for (auto ch: titlu)
        if(!std::isalpha(ch) && !std::isblank(ch))
            throw InvalidFieldException("Titlul nu este valid!\n");
}

void Validator::validDescriere(const TypeDescriere & descriere)  {
    if (descriere.empty() == 1)
        throw InvalidFieldException("Descrierea nu este valida!\n");
    for (auto ch: descriere)
        if(!std::isalnum(ch) && !std::isblank(ch))
            throw InvalidFieldException("Descrierea nu este valida!\n");
}

void Validator::validTip(const TypeTip & tip) {
    if (tip.empty() == 1)
        throw InvalidFieldException("Tipul  nu este valid!\n");
    for (auto ch: tip)
        if(!std::isalnum(ch) && !std::isblank(ch))
            throw InvalidFieldException("Tipul  nu este valid!\n");
}

void Validator::validDurata(const TypeDurata &durata) {
    if(durata > 0 && durata < 10000);
    else throw InvalidFieldException("Durata nu este valida!\n");
}

void Validator::validActivitate(const Activitate & activitate) {
    ValidatorException v;
    try{ validTitlu(activitate.getTitlu());}
    catch(InvalidFieldException& ie) {v += ie;}
    try{ validDescriere(activitate.getDescriere()); }
    catch(InvalidFieldException& ie) {v += ie;}
    try{ validTip(activitate.getTip());}
    catch(InvalidFieldException& ie) {v += ie;}
    try { validDurata(activitate.getDurata()); }
    catch(InvalidFieldException& ie) {v += ie;}
    if((int)v != 0) throw v;
}