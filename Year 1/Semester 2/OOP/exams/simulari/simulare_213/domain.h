//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef SIMULARE_213_DOMAIN_H
#define SIMULARE_213_DOMAIN_H
#include <string>
#include <sstream>
#include <ostream>
#include <iostream>

using std::string;
using std::istream;
class Apartament {
private:
    int suprafata;
    string strada;
    double pret;
public:
    Apartament() = default;
    Apartament(const int suprafata, const string& strada, const double pret) : suprafata {suprafata}, strada {strada}, pret {pret} {};
    friend istream& operator>>(istream& in, Apartament& apartament);
    bool operator==(const Apartament& apartament) const;
    int get_suprafata() const;
    string get_strada() const;
    double get_pret() const;
    string to_string() const;

    ~Apartament() = default;
};


#endif //SIMULARE_213_DOMAIN_H
