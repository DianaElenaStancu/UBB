//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_217_DOMAIN_H
#define SIMULARE_217_DOMAIN_H
#include <string>
#include <sstream>
#include <istream>
using std::string;
using std::istream;
class Device {
private:
    string tip;
    string model;
    int an;
    string culoare;
    double pret;
public:
    Device() = default;
    Device(const string& tip, const string& model, const int an, const string& culoare, const double pret) : tip { tip }, model { model }, an { an }, culoare { culoare }, pret { pret } {};
    string get_tip() const;
    string get_model() const;
    int get_an() const;
    string get_culoare() const;
    double get_pret() const;

    friend istream& operator>>(istream &in, Device& device);
    bool operator==(Device& device);
    string to_string() const;
};


#endif //SIMULARE_217_DOMAIN_H
