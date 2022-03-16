//
// Created by Diana-Elena Stancu on 14/03/2022.
//

#ifndef PROBLEMA006_VALIDATOR_H
#define PROBLEMA006_VALIDATOR_H
#include "domain.h"
#include <stdbool.h>

typedef bool (*Validator)(MATERIE, char*);

/*
 * functia valideaza o materie
 *
 * @parametrii: Materie - o materie
 *              erori - erori
 * @return: 1 - daca materia este valida
 *          0 - altfel
 */
bool ValideazaMaterie(MATERIE Materie, char* erori);

#endif //PROBLEMA006_VALIDATOR_H
