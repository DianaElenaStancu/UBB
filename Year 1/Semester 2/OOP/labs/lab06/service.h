//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#ifndef LAB06_SERVICE_H
#define LAB06_SERVICE_H

#include <type_traits>
#include <string>
#include <sstream>
#include "domain.h"
#include "validator.h"
#include "repository.cpp"
#include "repository.h"

class Service{
private:
    Repository<Activitate> repository;
public:
    // doar constructor fara parametrii
    Service()=default;
    Service(const Service&) = delete;
    //template<class T>
    //Service(const Repository<T>&) = delete;

    // adauga elementul in repository
    // arunca ServiceException daca nu a putut fi creat
    // arunca RepoException daca exista in container
    // arunca ValidatorException daca nu este valid
    void addSRV(const TypeTitlu &, const TypeDescriere &, const TypeTip&, const TypeDurata &);

    // sterge elementul din repository
    // arunca RepoException daca elementul nu exista
    // arunca ValidatorException daca nu este valid
    void removeSRV(const TypeTitlu &, const TypeDescriere &, const TypeTip &, const TypeDurata&);

    // modific primul elemet cu al doilea
    // arunca RepoException daca elementul nu exista
    // arunca ValidatorException daca unul din locatari nu este valid
    void modifySRV(const TypeTitlu &, const TypeDescriere &, const TypeTip &, const TypeDurata&, const TypeTitlu &, const TypeDescriere &, const TypeTip &, const TypeDurata&);

    // cauta apartamentul cu numarul dat
    // arunca ServiceException daca nu exista un astfel de apartament
    // arunca InvalidFieldException daca nu este valid
    Activitate findSRV(const TypeTitlu &);

    // returnez toate elementele care au tipul dat
    // arunca InvalidFieldException daca nu este valid
    Repository<Activitate> filterDescriere(const TypeDescriere&);

    // returnez toate elementele care au suprafata data?
    // arunca InvalidFieldException daca nu este valid
    Repository<Activitate> filterTip(const TypeTip &);

    // sortez repository-ul dupa tilu crescator
    void sortTitlu();

    // sortez repository-ul dupa descriere crescator
    void sortDescriere();

    // sortez repository-ul dupa tip, iar la tipuri egale sortez dupa durata
    void sortTipDurata();

    // implementare iteratori de begin si end pentru a putea intera
    Activitate* begin();
    Activitate* end();
    //const Activitate* cbegin() const;
    //const Activitate* cend() const;
};


#endif //LAB06_SERVICE_H
