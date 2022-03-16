//
// Created by Diana-Elena Stancu on 14/03/2022.
//

#include "domain.h"

bool CreeazaMaterie(MATERIE_P* Materie, char* Nume, char* Producator, int Cantitate) {
    if (Materie == NULL) return 0;

    MATERIE_P m = (MATERIE_P)malloc(sizeof(MATERIE));

    if (m == NULL) return 0;

    int numeLen = strlen(Nume) + 1;
    char* n = (char*) malloc(sizeof(char) * numeLen);
    strcpy(n, Nume);
    m->Nume = n;

    int producatorLen = strlen(Producator) + 1;
    char* p = (char*) malloc(sizeof(char) * producatorLen);
    strcpy(p, Producator);
    m->Producator = p;

    m->Cantitate = Cantitate;

    *Materie = m;
    return 1;
}

bool DistrugeMaterie(MATERIE_P* Materie) {
    if (Materie == NULL) return 0;
    free((*Materie)->Nume);
    free((*Materie)->Producator);
    free(*Materie);
    *Materie = NULL;
    return 1;
}

void PrintMaterie(MATERIE Materie) {
    printf("[Nume: %s; Producator: %s; Cantitate: %d;]\n", Materie.Nume, Materie.Producator, Materie.Cantitate);
}

char*  GetNume(MATERIE Materie) {
    return Materie.Nume;
}

char* GetProducator(MATERIE Materie) {
    return Materie.Producator;
}

int GetCantitate(MATERIE Materie) {
    return Materie.Cantitate;
}

void SetNume(MATERIE_P Materie, char *Nume) {
    int numeLen = strlen(Nume) + 1;
    char* numeNou = (char*) malloc(sizeof(char) * numeLen);
    if (numeNou == NULL)
        return;
    strcpy(numeNou, Nume);
    free(Materie->Nume);
    Materie->Nume = numeNou;
}

void SetProducator(MATERIE_P Materie, char *Producator) {
    int producatorLen = strlen(Producator) + 1;
    char* numeNou = (char*) malloc(sizeof(char) * producatorLen);
    if (numeNou == NULL) return;
    strcpy(numeNou, Producator);
    free(Materie->Producator);
    Materie->Producator = numeNou;
}

void SetCantitate(MATERIE_P Materie, int Cantitate) {
    Materie->Cantitate = Cantitate;
}

bool MateriiEgale(MATERIE Materie1, MATERIE Materie2) {
    if (strcmp(Materie1.Nume, Materie2.Nume) == 0) return 1;
    return 0;
}

bool ComparaCrescatorCantitate(MATERIE Materie1, MATERIE Materie2){
    if (GetCantitate(Materie1) < GetCantitate(Materie2))
        return 1;
    if (GetCantitate(Materie1) == GetCantitate(Materie2) && strcmp(GetNume(Materie1), GetNume(Materie2)) < 0)
        return 1;
    return 0;
}

bool ComparaCrescatorNume(MATERIE Materie1, MATERIE Materie2) {
    if (strcmp(GetNume(Materie1), GetNume(Materie2)) < 0) return 1;
    if (strcmp(GetNume(Materie1), GetNume(Materie2)) == 0 && GetCantitate(Materie1) < GetCantitate(Materie2)) return 1;
    return 0;
}

bool ComparaDescrescatorCantitate(MATERIE Materie1, MATERIE Materie2) {
    if (GetCantitate(Materie1) > GetCantitate(Materie2))return 1;
    if (GetCantitate(Materie1) == GetCantitate(Materie2) && strcmp(GetNume(Materie1), GetNume(Materie2)) > 0)return 1;
    return 0;
}

bool ComparaDescrescatorNume(MATERIE Materie1, MATERIE Materie2) {
    if (strcmp(GetNume(Materie1), GetNume(Materie2)) > 0) return 1;
    if (strcmp(GetNume(Materie1), GetNume(Materie2)) == 0 && GetCantitate(Materie1) > GetCantitate(Materie2)) return 1;
    return 0;
}