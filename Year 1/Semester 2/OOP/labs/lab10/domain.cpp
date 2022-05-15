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
    string line, sep;
    getline(in, line);
    istringstream input(line);
    input>>obj.Titlu >> sep;
    input>>obj.Descriere >> sep;
    input>>obj.Tip >> sep;
    input>>obj.Durata;
    return in;
}

ostream& operator<<(ostream& out, const Activitate& obj) {
    out << obj.Titlu << " ; " << obj.Descriere << " ; " << obj.Tip << " ; " << obj.Durata << '\n';
    return out;
}

string Activitate::toString() const {
    std::ostringstream out;
    out<<std::setw(3)<<Titlu<<' ';
    out<<std::setw(15)<<Descriere<<' ';
    out<<std::setw(7)<<Tip<<' ';
    out<<std::setw(15)<<Durata<<' ';
    return string(out.str());
}

Activitate Activitate::fromString(const string& txt) {
    std::istringstream in(txt);
    Activitate rez;
    in>>rez;
    return rez;
}