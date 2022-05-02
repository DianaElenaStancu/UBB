//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#include "repository.h"
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
    auto it = find_if(lista.begin(), lista.end(), [&](const Activitate &a){return activitate.getTitlu() == a.getTitlu();});
    if (it == lista.end())
        throw RepositoryException("Activitate inexistenta!\n");
    return *it;
}

unsigned int Repository::size() const noexcept {
    return lista.size();
}

void Repository::remove(const Activitate& activitate) {
    find(activitate);
    for (unsigned int i = 0; i < size(); ++i) {
        if (lista.at(i) == activitate) {
            lista.erase(lista.begin() + i);
        }
    }
}

void Repository::modify(Activitate& activitate, Activitate& activitate_noua) {
    find(activitate);
    for (auto& a : lista) {
        if (a == activitate) {
            a.setDurata(activitate_noua.getDurata());
            a.setTip(activitate_noua.getTip());
            a.setDescriere(activitate_noua.getDescriere());
            a.setTitlu(activitate_noua.getTitlu());
            return;
        }
    }
}

const vector<Activitate>& Repository::getAll() const noexcept{
    return lista;
}
