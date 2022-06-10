//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef STANCU_DIANA_SIMULARE_DOMAIN_H
#define STANCU_DIANA_SIMULARE_DOMAIN_H
#include <string>
#include <sstream>
#include <strstream>
using std::string;
using std::istream;
using std::ostream;
class Elev {
private:
    string cod;
    string nume;
    string prenume;
    int clasa;
    double medie;
public:

    //constructorii
    Elev() = default;
    Elev(const string& cod, const string& nume, const string& prenume, const int clasa, const double medie) :
    cod {cod}, nume{nume}, prenume{prenume}, clasa{clasa}, medie{medie} {};

    //gettere
    string get_cod() const;
    string get_nume() const;
    string get_prenume() const;
    int get_clasa() const;
    double get_medie() const;
    //conversie obiect in string pentru a-l putea afisa in consola
    string to_string() const;

    //suprascriere de operatori
    friend istream& operator >>(istream &in, Elev &elev);
    bool operator==(Elev &elev);
};

void test_domain();
#endif //STANCU_DIANA_SIMULARE_DOMAIN_H
