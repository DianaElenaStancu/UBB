//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#ifndef LAB05_SERVICE_H
#define LAB05_SERVICE_H
#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "domain.h"
#include "infrastructure.h"
#include "validator.h"
#include "utils.h"
#include "repository.h"
#include <string.h>

#define oo 0x3f3f3f3f

typedef struct _SERVICE_CHELTUIELI {
    REPOSITORY* Repository;
    ValidationFunction ValidateCheltuiala;
} SERVICE_CHELTUIELI, * PSERVICE_CHELTUIELI;

SERVICE_CHELTUIELI CreateService(REPOSITORY* Repository, ValidationFunction Validation);

int StoreCheltuiala(PSERVICE_CHELTUIELI Service, int Id, int NumarApartament, double Suma, char* Tip, char* errors);

int EraseCheltuiala(PSERVICE_CHELTUIELI Service, int Id, char* errors);

int ChangeCheltuiala(PSERVICE_CHELTUIELI Service, int Id, int NumarApartament, double Suma, char* Tip, char* errors);

DYNAMIC_VECTOR * ViewCheltuieli(PSERVICE_CHELTUIELI Service, int Mode, int AscendingMode, char* errors);

DYNAMIC_VECTOR * FilterCheltuieli(PSERVICE_CHELTUIELI Service, int NumarApartament, double Suma, char* Tip, int Mode, char* errors);

int DestroyService(PSERVICE_CHELTUIELI Service);

int Undo(PSERVICE_CHELTUIELI Service);

void TestService();

#endif
#endif //LAB05_SERVICE_H
