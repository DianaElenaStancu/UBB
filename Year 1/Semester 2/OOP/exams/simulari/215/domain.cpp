//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "domain.h"
int Joc::get_index() const{
    return this->index;
}
string Joc::get_titlu() const{
    return this->titlu;
}
int Joc::get_pret() const{
    return this->pret;
}
string Joc::get_platforma() const{
    return this->platforma;
}
int Joc::get_rating() const{
    return this->rating;
}
istream& operator >>(istream& in, Joc &joc){
    string line, sep;
    sep = ",";
    getline(in, line);
    joc.index = stoi(line.substr(0, line.find(sep)));
    line.erase(0, line.find(sep) + 1);
    joc.titlu = line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    joc.pret = stoi(line.substr(0, line.find(sep)));
    line.erase(0, line.find(sep) + 1);
    joc.platforma = line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    joc.rating = stoi(line.substr(0, line.find(sep)));
    line.erase(0, line.find(sep) + 1);
    return in;
}

ostream& operator <<(ostream& out, Joc &joc){
    out << joc.index << "," << joc.titlu << "," << joc.pret << "," << joc.platforma << "," << joc.rating << "\n";
    return out;
}

bool Joc::operator==(Joc &joc){
    return this->index == joc.get_index() && this->titlu == joc.get_titlu() && this->rating == joc.get_rating() &&
    this->get_pret() == joc.get_pret() && this->get_platforma() == joc.get_platforma();
}
string Joc::to_string() const{
    return this->titlu + " " + std::to_string(this->pret)+ "\n";
}
void test_domain() {
    Joc j1(1, "God Of War",90,"PlayStation",18), j2;
    std::strstream sout;
    sout << j1;
    sout >> j2;
    assert(j1 == j2);
}