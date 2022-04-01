//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#include "domain.h"
#include <iostream>
using namespace std;
Activitate::Activitate(const Activitate & obj) {
    Titlu = obj.Titlu;
    Descriere = obj.Descriere;
    Tip = obj.Tip;
    Durata = obj.Durata;
    cout << "obiect creat\n";
}

Activitate& Activitate::operator=(const Activitate & obj) = default;

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


istream& operator>>(istream& in, Activitate& obj) {
    in>>obj.Titlu;
    in>>obj.Descriere;
    in>>obj.Tip;
    in>>obj.Durata;
    return in;
}

ostream& operator<<(ostream& out, const Activitate& obj) {
    out << obj.Titlu << ' ' << obj.Descriere << ' ' << obj.Tip << ' ' << obj.Durata;
    return out;
}