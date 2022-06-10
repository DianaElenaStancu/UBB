//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "domain.h"


string Elev::get_cod() const {
    return this->cod;
}

string Elev::get_nume() const {
    return this->nume;
}

string Elev::get_prenume() const {
    return this->prenume;
}

int Elev::get_clasa() const {
    return this->clasa;
}

double Elev::get_medie() const {
    return this->medie;
}

istream& operator >>(istream &in, Elev &elev) {
    string line, sep = ",";
    getline(in, line);
    elev.cod = line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    elev.nume = line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    elev.prenume = line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    elev.clasa = stoi(line.substr(0, line.find(sep)));
    line.erase(0, line.find(sep) + 1);
    elev.medie = stod(line.substr(0, line.find(sep)));
    line.erase(0, line.find(sep) + 1);
    return in;
}


bool Elev::operator==(Elev &elev) {
    return elev.cod == this->cod;
}

string Elev::to_string() const {
    return cod + " " + nume + "\n";
}

void test_domain() {
    Elev e1, e2 {"06660","Nume1","Prenume1",9,10};
    assert(e2.get_cod() == "06660");
    assert(e2.get_nume() == "Nume1");
    assert(e2.get_prenume() == "Prenume1");
    assert(e2.get_medie() == 10);
    assert(e2.get_clasa() == 9);
    assert(e2.to_string() == "06660 Nume1\n");
    std::strstream sout;
    try {
        sout >> e1;
    } catch(...) {

    }

}