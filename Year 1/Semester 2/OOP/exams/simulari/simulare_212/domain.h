//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_212_DOMAIN_H
#define SIMULARE_212_DOMAIN_H
#include <string>
#include <sstream>
#include <fstream>
using std::string;
using std::istream;
using std::ostream;
using std::ifstream;
class Procesor {
private:
    string nume;
    int nrThreaduri;
    string socluProcesor;
    double pret;
public:
    Procesor() = default;
    Procesor(const string& nume, const int nrThreaduri, const string& socluProcesor, const double pret) : nume { nume }, nrThreaduri { nrThreaduri }, socluProcesor { socluProcesor }, pret { pret } {};
    string get_nume();
    int get_nr_threaduri();
    string get_soclu();
    double get_pret();
    friend istream& operator>>(istream &in, Procesor &procesor);
    bool operator ==(const Procesor &procesor) const;
    string to_string() const;
};

class PlacaDeBaza {
private:
    string nume;
    string socluProcesor;
    double pret;
public:
    PlacaDeBaza() = default;
    PlacaDeBaza(const string& nume, const string& socluProcesor, const double pret) : nume { nume }, socluProcesor { socluProcesor }, pret { pret } {};
    string get_nume();
    string get_soclu();
    double get_pret();
    friend istream& operator>>(istream &in, PlacaDeBaza &placa);
    friend ostream& operator<<(ostream &out, PlacaDeBaza &placa);
    bool operator==(const PlacaDeBaza& placa) const;
    string to_string() const;
};

void test_domain();

#endif //SIMULARE_212_DOMAIN_H
