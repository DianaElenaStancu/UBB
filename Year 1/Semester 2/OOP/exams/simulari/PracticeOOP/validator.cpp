//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#include "validator.h"

const bool Validator::esteNrInmatriculare(const string &nrInmatriculare) const {
    if(nrInmatriculare.length() != 7)
        return false;
    for (const auto& indice: { 0, 1, 4, 5, 6})
        if (!isupper(nrInmatriculare.at(indice)))
            return false;
    for (const auto& indice: {2, 3})
        if (!isdigit(nrInmatriculare.at(indice)))
            return false;
    return true;
}

void Validator::validate(const Masina &masina) const {
    vector <string> errors;
    if (!esteNrInmatriculare(masina.GetNrInmatriculare()))
        errors.push_back("nr inmatriculare invalid\n");
    if (masina.GetProducator() == "")
        errors.push_back("producator invalid\n");
    if (masina.GetTip() == "")
        errors.push_back("tip invalid\n");
    if (masina.GetModel() == "")
        errors.push_back("model invalid\n");
    if (errors.size() > 0)
        throw ValidatorException(errors);
}