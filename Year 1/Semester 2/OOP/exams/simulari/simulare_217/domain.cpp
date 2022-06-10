//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "domain.h"

string Device::get_tip() const{
    return this->tip;
}
string Device::get_model() const{
    return this->model;
}
int  Device::get_an() const{
    return this->an;
}
string  Device::get_culoare() const{
    return this->culoare;
}
double  Device::get_pret() const{
    return this->pret;
}

istream& operator>>(istream &in, Device& device){
    string line, now;
    getline(in, line);
    std::istringstream input(line);
    input >> device.tip; input >> now;
    input >> device.model; input >> now;
    input >> device.an; input >> now;
    input >> device.culoare; input >> now;
    input >> device.pret; input >> now;
    return in;
}
bool  Device::operator==(Device& device){
    return device.get_tip() == this->tip && device.get_pret() == this->pret && device.get_an() == this->an &&
    device.get_culoare() == this->culoare && device.get_model() == this->model;
}
string  Device::to_string() const{
    return this->model + " " + this->culoare + " " + std::to_string(this->pret) + "\n";
}