//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#ifndef LAB05_DOMAIN_H
#define LAB05_DOMAIN_H
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _CHELTUIALA {
    int Id;
    int NumarApartament;
    double Suma;
    char* Tip;
} CHELTUIALA, *PCHELTUIALA;

typedef int (*comparerDouble)(double, double);
typedef int (*comparerChar)(char*, char*);

CHELTUIALA* CreateCheltuiala (int Id, int NumarApartament, double Suma, char* Tip);

CHELTUIALA* CopyCheltuiala (PCHELTUIALA Cheltuiala);

int GetId(PCHELTUIALA Cheltuiala);

void SetId(PCHELTUIALA Cheltuiala, int Id);

int GetNumarApartament(PCHELTUIALA Cheltuiala);

void SetNumarApartament(PCHELTUIALA Cheltuiala, int NumarApartament);

double GetSuma(PCHELTUIALA Cheltuiala);

void SetSuma(PCHELTUIALA Cheltuiala, double Suma);

char* GetTip(PCHELTUIALA Cheltuiala);

void SetTip(PCHELTUIALA Cheltuiala, char* Tip);

int CheltuialaEqual(PCHELTUIALA Cheltuiala1, PCHELTUIALA Cheltuiala2);

int CheltuialaEqualId(PCHELTUIALA Cheltuiala1, PCHELTUIALA Cheltuiala2);

void DestroyCheltuiala (PCHELTUIALA Cheltuiala);

void TestDomain();

#endif //LAB05_DOMAIN_H
