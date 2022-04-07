//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#include "repository.h"
#include <iostream>
using namespace std;
void Repository::add(const Activitate& activitate) {
    if (exista(activitate)) {
        throw RepositoryException("Activitatea deja existenta!\n");
    }
    lista.push_back(activitate);
}

bool Repository::exista(const Activitate& activitate) const {
    try {
        find(activitate);
        return true;
    }
    catch (const RepositoryException&) {
        return false;
    }
}

const Activitate& Repository::find(const Activitate& activitate) const {
    for (const auto& a : this->lista) {
        if (a == activitate) {
            return activitate;
        }
    }
    throw RepositoryException("Activitate inexistenta!\n");
}

unsigned int Repository::size() const noexcept {
    return lista.size();
}

void Repository::remove(const Activitate& activitate) {
    find(activitate);
    for (unsigned int i = 0; i < size(); ++i) {
        if (lista.at(i) == activitate) {
            lista.erase(i);
        }
    }
}

void Repository::modify(Activitate& activitate, Activitate& activitate_noua) {
    find(activitate);
    for (auto& a : lista) {
        if (a == activitate) {
            /*a.SetProducator(producator);
            masina.SetModel(model);
            masina.SetTip(tip);*/
            //activitate = activitate_noua;
            a.setDurata(activitate_noua.getDurata());
            a.setTip(activitate_noua.getTip());
            a.setDescriere(activitate_noua.getDescriere());
            a.setTitlu(activitate_noua.getTitlu());
            return;
        }
    }
}


const DynamicArray<Activitate>& Repository::getAll() const noexcept{
    return lista;
}
