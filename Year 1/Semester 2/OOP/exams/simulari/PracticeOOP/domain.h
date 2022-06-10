//
// Created by Diana-Elena Stancu on 15/05/2022.
//

#ifndef PRACTICEOOP_DOMAIN_H
#define PRACTICEOOP_DOMAIN_H
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>

using std::string;
using std::ostream;
using std::istream;

class Masina {
private:
    string nrInmatriculare;
    string producator;
    string model;
    string tip;
public:
    Masina() = default;
    Masina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) : nrInmatriculare {nrInmatriculare}, producator { producator }, model { model }, tip { tip }{};
    Masina(const Masina& ot) : nrInmatriculare{ ot.nrInmatriculare }, producator { ot.producator }, model { ot.model }, tip { ot.tip } {};
    ~Masina() noexcept {
        nrInmatriculare.clear();
        producator.clear();
        model.clear();
        tip.clear();
    }

    Masina& operator=(const Masina& ot);
    bool operator==(const Masina& ot) const;
    bool operator!=(const Masina& ot) const;
    friend ostream& operator<<(ostream& out, const Masina& masina);
    friend istream& operator>>(istream& in, Masina& masina);

    string GetNrInmatriculare() const;
    string GetProducator() const;
    string GetModel() const;
    string GetTip() const;
    void SetNrInmatriculare(const string& nrInmatriculare);
    void SetProducator(const string& producator);
    void SetModel(const string& model);
    void SetTip(const string& tip);
    string toString() const;
};


#endif //PRACTICEOOP_DOMAIN_H
