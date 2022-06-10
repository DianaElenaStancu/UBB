//
// Created by Diana-Elena Stancu on 15/05/2022.
//

#include "domain.h"

Masina& Masina::operator=(const Masina& ot)  = default;

bool Masina::operator==(const Masina& ot) const{
    return this->nrInmatriculare == ot.nrInmatriculare;
}

bool Masina::operator!=(const Masina& ot) const{
    return this->nrInmatriculare != ot.nrInmatriculare;
}

ostream& operator<<(ostream& out, const Masina& masina) {
    out << masina.nrInmatriculare << " | " << masina.producator << " | " << masina.model << " | " << masina.tip << std::endl;
    return out;
}

istream& operator>>(istream& in, Masina& masina) {
    string line, now;
    getline(in, line);
    std::istringstream input(line);
    input >> masina.nrInmatriculare; input >> now;
    input >> masina.producator; input >> now;
    input >> masina.model; input >> now;
    input >> masina.tip;

    return in;
}

string Masina::GetNrInmatriculare() const {
    return this->nrInmatriculare;
}

string Masina::GetProducator() const {
    return this->producator;
}

string Masina::GetModel() const {
    return this->model;
}

string Masina::GetTip() const {
    return this->tip;
}

void Masina::SetNrInmatriculare(const string& nrInmatriculare) {
    this->nrInmatriculare = nrInmatriculare;
}

void Masina::SetProducator(const string& producator) {
    this->producator = producator;
}

void Masina::SetModel(const string& model) {
    this->model = model;
}

void Masina::SetTip(const string& tip) {
    this->tip = tip;
}

string Masina::toString() const{
    return nrInmatriculare + " " + producator + " " + model + " " + tip + '\n';
}