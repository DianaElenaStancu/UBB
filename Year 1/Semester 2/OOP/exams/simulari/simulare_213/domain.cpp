//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#include "domain.h"

istream& operator>>(istream& in, Apartament& apartament){
    string line, now;
    getline(in, line);
    std::istringstream input(line);
    input >> apartament.strada; input >> now;
    input >> apartament.suprafata; input >> now;
    input >> apartament.pret; input >> now;
    return in;
}

bool Apartament::operator==(const Apartament& apartament) const {
    return apartament.get_pret() == this->pret && apartament.get_strada() == this->strada && apartament.get_suprafata() == this->suprafata;
}

int Apartament::get_suprafata() const{
    return this->suprafata;
}
string Apartament::get_strada() const{
    return this->strada;
}
double Apartament::get_pret() const{
    return this->pret;
}
string Apartament::to_string() const {
    return this->get_strada() + " " + std::to_string(this->suprafata) + " m^2 " + std::to_string(this->get_pret()) + " euro\n";
}
void test_domain() {

}