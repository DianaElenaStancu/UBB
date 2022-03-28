//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#ifndef LAB05_VALIDATOR_H
#define LAB05_VALIDATOR_H
#include "domain.h"

typedef int (*ValidationFunction)(CHELTUIALA*, char*);

int ValidateCheltuiala(CHELTUIALA* Cheltuiala, char* errors);

void TestValidator();

#endif //LAB05_VALIDATOR_H
