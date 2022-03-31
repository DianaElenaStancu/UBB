//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "domain.h"

CHELTUIALA* CreateCheltuiala (int Id, int NumarApartament, double Suma, char* Tip) {
    CHELTUIALA* Cheltuiala = (CHELTUIALA*)malloc(sizeof (CHELTUIALA));
    if (Cheltuiala == NULL)
        return NULL;
    Cheltuiala->Id = Id;
    Cheltuiala->NumarApartament = NumarApartament;
    Cheltuiala->Suma = Suma;

    unsigned TipLen = strlen(Tip) + 1;
    char* tip = (char*)malloc(sizeof (char) * TipLen);
    if (tip == NULL)
        return NULL;
    strcpy (tip, Tip);
    Cheltuiala->Tip = tip;

    return Cheltuiala;
}

void DestroyCheltuiala (PCHELTUIALA Cheltuiala) {
    if (Cheltuiala == NULL)
        return;
    free(Cheltuiala->Tip);
    free(Cheltuiala);
}

CHELTUIALA* CopyCheltuiala (PCHELTUIALA Cheltuiala) {
    return CreateCheltuiala(Cheltuiala->Id, Cheltuiala->NumarApartament, Cheltuiala->Suma, Cheltuiala->Tip);
}

int GetId (PCHELTUIALA Cheltuiala) {
    return Cheltuiala->Id;
}

void SetId (PCHELTUIALA Cheltuiala, int Id) {
    Cheltuiala->Id = Id;
}

int GetNumarApartament (PCHELTUIALA Cheltuiala) {
    return Cheltuiala->NumarApartament;
}

void SetNumarApartament (PCHELTUIALA Cheltuiala, int NumarApartament) {
    Cheltuiala->NumarApartament = NumarApartament;
}

double GetSuma (PCHELTUIALA Cheltuiala) {
    return Cheltuiala->Suma;
}

void SetSuma (PCHELTUIALA Cheltuiala, double Suma) {
    Cheltuiala->Suma = Suma;
}

char* GetTip (PCHELTUIALA Cheltuiala) {
    return Cheltuiala->Tip;
}

void SetTip (PCHELTUIALA Cheltuiala, char* Tip) {
    unsigned TipLen = strlen(Tip) + 1;
    char* NewTip = (char*)malloc(sizeof (char) * TipLen);
    if (NewTip == NULL)
        return;
    strcpy(NewTip, Tip);
    free(Cheltuiala->Tip);
    Cheltuiala->Tip = NewTip;
}

int CheltuialaEqual(PCHELTUIALA Cheltuiala1, PCHELTUIALA Cheltuiala2) {
    return (Cheltuiala1->Id == Cheltuiala2->Id) && (Cheltuiala1->NumarApartament == Cheltuiala2->NumarApartament) && (Cheltuiala1->Suma == Cheltuiala2->Suma) && strcmp(Cheltuiala1->Tip, Cheltuiala2->Tip) == 0;
}

int CheltuialaEqualId(PCHELTUIALA Cheltuiala1, PCHELTUIALA Cheltuiala2) {
    return (Cheltuiala1->Id == Cheltuiala2->Id);
}

static int compareIncreasingDouble(const double a, const double b) {
    return a < b;
};
static int compareDecreasingDouble(const double a, const double b) {
    return a > b;
};

static int compareIncreasingChar(const char* a, const char* b) {
    return strcmp(a, b) < 0;
};
static int compareDecreasingChar(const char* a, const char* b) {
    return strcmp(a, b) > 0;
};

int CompareSuma(PCHELTUIALA Cheltuiala1, PCHELTUIALA Cheltuiala2, comparerDouble comparer) {
    return comparer(Cheltuiala1->Suma, Cheltuiala2->Suma);
}

int CompareTip(PCHELTUIALA Cheltuiala1, PCHELTUIALA Cheltuiala2, comparerChar comparer) {
    return comparer(Cheltuiala1->Tip, Cheltuiala2->Tip);
}

//tests
static void TestCreateAndDestroy() {
    CHELTUIALA* Cheltuiala;
    Cheltuiala = CreateCheltuiala(6, 1, 200.34, "apa");
    assert(Cheltuiala->Id == 6);
    assert(Cheltuiala->NumarApartament == 1);
    assert(Cheltuiala->Suma == 200.34);
    assert(strcmp(Cheltuiala->Tip, "apa") == 0);
    DestroyCheltuiala(Cheltuiala);
}

static void TestGetAndSet() {
    CHELTUIALA* Cheltuiala = CreateCheltuiala(6, 1, 200.34, "apa");
    SetId(Cheltuiala, 7);
    assert(GetId(Cheltuiala) == 7);
    SetNumarApartament(Cheltuiala, 23);
    assert(GetNumarApartament(Cheltuiala) == 23);
    SetSuma(Cheltuiala, 300.56);
    assert(GetSuma(Cheltuiala) == 300.56);
    SetTip(Cheltuiala, "gaz");
    assert(strcmp(GetTip(Cheltuiala), "gaz") == 0);

    DestroyCheltuiala(Cheltuiala);
}

static void TestCompare() {
    CHELTUIALA* Cheltuiala = CreateCheltuiala(6, 1, 200.34, "apa");
    CHELTUIALA* CheltuialaIdentic = CreateCheltuiala(6, 1, 200.34, "apa");
    CHELTUIALA* CheltuialaDiferit = CreateCheltuiala(7, 1, 200.34, "apa");
    CHELTUIALA* CheltuialaCopy = CopyCheltuiala(Cheltuiala);

    assert(CheltuialaEqual(Cheltuiala, CheltuialaCopy));
    assert(CheltuialaEqualId(Cheltuiala, CheltuialaCopy));
    assert(CheltuialaEqual(Cheltuiala, CheltuialaIdentic));
    assert(CheltuialaEqual(CheltuialaDiferit, CheltuialaIdentic) == 0);
    DestroyCheltuiala(CheltuialaDiferit);
    CheltuialaDiferit = CreateCheltuiala(6, 2, 200.34, "apa");
    assert(CheltuialaEqual(CheltuialaDiferit, CheltuialaIdentic) == 0);
    DestroyCheltuiala(CheltuialaDiferit);
    CheltuialaDiferit = CreateCheltuiala(6, 1, 200.30, "apa");
    assert(CheltuialaEqual(CheltuialaDiferit, CheltuialaIdentic) == 0);
    DestroyCheltuiala(CheltuialaDiferit);
    CheltuialaDiferit = CreateCheltuiala(6, 1, 200.34, "gaz");
    assert(CheltuialaEqual(CheltuialaDiferit, CheltuialaIdentic) == 0);

    DestroyCheltuiala(CheltuialaDiferit);
    CheltuialaDiferit = CreateCheltuiala(6, 1, 200.30, "gaz");
    assert(CompareSuma(Cheltuiala, CheltuialaDiferit, compareIncreasingDouble) == 0);
    assert(CompareSuma(Cheltuiala, CheltuialaDiferit, compareDecreasingDouble) == 1);
    assert(CompareTip(Cheltuiala, CheltuialaDiferit, compareIncreasingChar) == 1);
    assert(CompareTip(Cheltuiala, CheltuialaDiferit, compareDecreasingChar) == 0);

    DestroyCheltuiala(CheltuialaDiferit);
    DestroyCheltuiala(CheltuialaIdentic);
    DestroyCheltuiala(Cheltuiala);
    DestroyCheltuiala(CheltuialaCopy);
}

void TestDomain() {
    TestCreateAndDestroy();
    TestGetAndSet();
    TestCompare();
}
