//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#include "domain.h"

Activitate::Activitate(const Activitate & obj) {
    Titlu = obj.Titlu;
    Descriere = obj.Descriere;
    Tip = obj.Tip;
    Durata = obj.Durata;
}

Activitate& Activitate::operator=(const Activitate & obj) {
    Titlu = obj.Titlu;
    Descriere = obj.Descriere;
    Tip = obj.Tip;
    Durata = obj.Durata;
    return *this;
}

TypeTitlu Activitate::getTitlu() const {
    return Titlu;
}

TypeDescriere Activitate::getDescriere() const {
    return Descriere;
}

TypeTip Activitate::getTip() const {
    return Tip;
}

TypeDurata Activitate::getDurata() const {
    return Durata;
}

void Activitate::setTitlu(const TypeTitlu& valoare) {
    Titlu = valoare;
}

void Activitate::setDescriere(const TypeDescriere & valoare) {
    Descriere = valoare;
}

void Activitate::setTip(const TypeTip & valoare) {
    Tip = valoare;
}

void Activitate::setDurata(const TypeDurata & valoare) {
    Durata = valoare;
}

bool Activitate::operator==(const Activitate& obj) const {
    return Titlu == obj.Titlu &&
    Descriere == obj.Descriere &&
    Tip == obj.Tip &&
    Durata == obj.Durata;
}

bool Activitate::operator!=(const Activitate& obj) const {
    return !(*this == obj);
}

bool Activitate::operator<(const Activitate& obj) const {
    return Titlu < obj.Titlu;
}

bool Activitate::operator>(const Activitate& obj) const {
    return !(*this == obj) && !(*this < obj);
}

bool Activitate::operator<=(const Activitate& obj) const {
    return !(*this > obj);
}

bool Activitate::operator>=(const Activitate& obj) const {
    return !(*this < obj);
}