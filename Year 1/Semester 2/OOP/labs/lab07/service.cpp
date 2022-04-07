//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#include "service.h"
#include <iostream>
using namespace std;
void Service::addSRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata) {
    Activitate activitate{titlu, descriere, tip, durata};
    Validator::validActivitate(activitate);
    repository.add(activitate);
}

void Service::removeSRV(const TypeTitlu &titlu, const TypeDescriere &descriere, const TypeTip &tip, const TypeDurata& durata) {
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
    repository.modify(activitate, activitate_noua);
}

Activitate Service::findSRV(const TypeTitlu& titlu) {
    auto lista = repository.getAll();
    for (auto &a: lista) {
        if (a.getTitlu() == titlu)
            return a;
    }
    throw ServiceException("Activitate inexistenta!");
}

DynamicArray<Activitate> Service::filterDescriere(const TypeDescriere & descriere) {
    Validator::validDescriere(descriere);
    DynamicArray<Activitate> result{};
    auto tot = repository.getAll();

    for (const auto& a : tot) {
        if (a.getDescriere() == descriere) {
            result.push_back(a);
        }
    }
    return result;
}

DynamicArray<Activitate> Service::filterTip(const TypeTip & tip) {
    Validator::validTip(tip);
    DynamicArray<Activitate> result{};
    auto tot = repository.getAll();

    for (const auto& a : tot) {
        if (a.getTip() == tip) {
            result.push_back(a);
        }
    }
    return result;
}


DynamicArray<Activitate> Service::sortTitlu() {
    auto sorted{ getAll() };
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < static_cast<int>(sorted.size()) - 1; i += 1) {
            if (sorted.at(i).getTitlu() > sorted.at(i + 1).getTitlu()) { auto aux = sorted.at(i);
                sorted.at(i) = sorted.at(i + 1);
                sorted.at(i + 1) = aux;
                change = true;
            }
        }
    }
    return sorted;
}

DynamicArray<Activitate> Service::sortDescriere() {
    auto sorted{ getAll() };
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < static_cast<int>(sorted.size()) - 1; i += 1) {
            if (sorted.at(i).getDescriere() > sorted.at(i + 1).getDescriere()) {
                auto aux = sorted.at(i);
                sorted.at(i) = sorted.at(i + 1);
                sorted.at(i + 1) = aux;
                change = true;
            }
        }
    }
    return sorted;
}

DynamicArray<Activitate> Service::sortTipDurata() {
    auto sorted{ getAll() };
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < static_cast<int>(sorted.size()) - 1; i += 1) {
            if (sorted.at(i).getTip() > sorted.at(i + 1).getTip() || (sorted.at(i).getTip() == sorted.at(i + 1).getTip() && sorted.at(i).getDurata() > sorted.at(i + 1).getDurata())) {
                auto aux = sorted.at(i);
                sorted.at(i) = sorted.at(i + 1);
                sorted.at(i + 1) = aux;
                change = true;
            }
        }
    }
    return sorted;
}

const DynamicArray<Activitate>& Service::getAll() const noexcept {
    return repository.getAll();
}