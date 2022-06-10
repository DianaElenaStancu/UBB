//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#ifndef PRACTICEOOP_VALIDATOR_H
#define PRACTICEOOP_VALIDATOR_H
#include "domain.h"
#include "exception.h"
#include <vector>
using std::vector;

class Validator {
private:
    const bool esteNrInmatriculare(const string& nrInmatriculare) const;
public:
    void validate(const Masina& masina) const;
};

class ValidatorException : public MultiStringException{
    vector <string> errors;
public:
    ValidatorException(const vector <string>& errors) : MultiStringException { errors } {};
};
#endif //PRACTICEOOP_VALIDATOR_H
