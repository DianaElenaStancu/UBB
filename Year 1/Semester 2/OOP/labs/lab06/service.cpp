//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#include "service.h"

#include "repository.hpp"

void Service::addSRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata) {
    Activitate activitate{titlu, descriere, tip, durata};
    Validator::validActivitate(activitate);
    repository.add(activitate);
}

void Service::removeSRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata) {
    Activitate activitate{titlu, descriere, tip, durata};
    Validator::validActivitate(activitate);
    repository.remove(activitate);
}

void Service::modifySRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata,
                     const TypeTitlu & titlu_nou, const TypeDescriere & descriere_noua, const TypeTip& tip_nou, const TypeDurata & durata_noua) {
    Activitate activitate{titlu, descriere, tip, durata};
    Activitate activitate_noua{titlu_nou, descriere_noua, tip_nou, durata_noua};
    Validator::validActivitate(activitate);
    Validator::validActivitate(activitate_noua);
    auto it = repository.find(activitate);
    if(it == nullptr) throw RepositoryException("Elementul nu a fost gasit!\n");
    *it = activitate_noua;
}

Activitate Service::findSRV(const TypeTitlu & titlu) {
    Validator::validTitlu(titlu);
    auto it = repository.find([&titlu](const Activitate& l){return l.getTitlu() == titlu; });
    if(it == nullptr) throw ServiceException("Activitatea nu exista!\n");
    return *it;
}

Repository<Activitate> Service::filterDescriere(const TypeDescriere & descriere) {
    Validator::validDescriere(descriere);
    Repository<Activitate> rez;
    auto pred = [&descriere](const Activitate &a)
    { return a.getDescriere() == descriere; };
    auto it = repository.find(pred);
    while(it != nullptr)
    {
        rez.add(*it);
        it = repository.find(pred, it+1);
    }
    return rez;
}


Repository<Activitate> Service::filterTip(const TypeTip & tip) {
    Validator::validTip(tip);
    Repository<Activitate> rez;
    auto pred = [&tip](const Activitate &a)
    { return a.getTip() == tip; };
    auto it = repository.find(pred);
    while(it != nullptr)
    {
        rez.add(*it);
        it = repository.find(pred, it+1);
    }
    return rez;
}



void Service::sortTitlu() {
    auto cmp = [](const Activitate& l1, const Activitate& l2)
    {
        return l1.getTitlu() < l2.getTitlu();
    };
    repository.sort(cmp);
}

void Service::sortDescriere() {
    auto cmp = [](const Activitate& l1, const Activitate& l2)
    {
        return l1.getDescriere() < l2.getDescriere();
    };
    repository.sort(cmp);
}

void Service::sortTipDurata() {
    auto cmp = [](const Activitate& l1, const Activitate& l2)
    {
        return  l1.getTip() < l2.getTip() ||
                l1.getTip() == l2.getTip() && l1.getDurata() < l2.getDurata();
    };
    repository.sort(cmp);
}

Activitate* Service::begin() { return repository.begin(); }
Activitate* Service::end() { return repository.end(); }
/*
const Activitate* Service::cbegin() const { return repository.cbegin(); }
const Activitate* Service::cend() const { return repository.cend(); }
*/
