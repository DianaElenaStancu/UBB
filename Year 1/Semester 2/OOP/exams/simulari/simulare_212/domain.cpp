//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "domain.h"

string Procesor::get_nume(){
    return this->nume;
}

int Procesor::get_nr_threaduri(){
    return this->nrThreaduri;
}

string Procesor::get_soclu(){
    return this->socluProcesor;
}

double Procesor::get_pret(){
    return this->pret;
}

istream& operator>>(istream &in, Procesor &procesor){
    string line, delimiter;
    getline(in, line);
    delimiter = ";";
    procesor.nume = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + 1);
    procesor.nrThreaduri = stoi(line.substr(0, line.find(delimiter)));
    line.erase(0, line.find(delimiter) + 1);
    procesor.socluProcesor = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + 1);
    procesor.pret = stod(line.substr(0, line.find(delimiter)));
    line.erase(0, line.find(delimiter) + 1);
    return in;
}

bool Procesor::operator ==(const Procesor &procesor) const {
    return procesor.nume == this->nume && procesor.nrThreaduri == this->nrThreaduri &&
    procesor.socluProcesor == this->socluProcesor && procesor.pret == this->pret;
}

string Procesor::to_string() const{
    return nume + " " + std::to_string(nrThreaduri) + "\n";
}

string PlacaDeBaza::get_nume(){
    return this->nume;
}

string PlacaDeBaza::get_soclu(){
    return this->socluProcesor;
}

double PlacaDeBaza::get_pret(){
    return this->pret;
}

istream& operator>>(istream &in, PlacaDeBaza &placa){
    string line, delimiter;
    getline(in, line);
    delimiter = ";";
    placa.nume = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + 1);
    placa.socluProcesor = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + 1);
    placa.pret = stod(line.substr(0, line.find(delimiter)));
    line.erase(0, line.find(delimiter) + 1);
    return in;
}

ostream& operator<<(ostream &out, PlacaDeBaza &placa){
    out << placa.nume << ";" << placa.socluProcesor << ";" << placa.pret << "\n";
    return out;
}

bool PlacaDeBaza::operator==(const PlacaDeBaza& placa) const{
    return placa.nume == this->nume && placa.pret == this->pret && placa.socluProcesor == this->socluProcesor;
}

string PlacaDeBaza::to_string() const {
    return nume;
}

void test_domain() {
    ifstream in("test.in", std::ios::in);
    if (!in.is_open())
        return;
    Procesor p1; Procesor p2("Ryzen 5",4600,"Intel 23g",645.6);
    in >> p1;
    assert(p1 == p2);
}