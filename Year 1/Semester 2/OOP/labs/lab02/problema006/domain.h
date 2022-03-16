//
// Created by Diana-Elena Stancu on 14/03/2022.
//

#ifndef PROBLEMA006_DOMAIN_H
#define PROBLEMA006_DOMAIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _MATERIE {
    char* Nume;
    char* Producator;
    int Cantitate;
}MATERIE, *MATERIE_P;


/*
 *  functia creeaza Materia prima din cofetarie si returneaza materia printr-un pointer
 *
 * @parametrii: Materie - pointer la un pointer la materie
 *              Id - integer
 *              Nume - pointer la un char
 *              Producator - pointer la un char
 *              Cantitate - integer
 * @return: 1 - daca Materia a fost creata cu succes
 *          0 - daca Materia nu a putut fi creata
 */
bool CreeazaMaterie(MATERIE_P* Materie, char* Nume, char* Producator, int Cantitate);

/*
 * functia distruge materia
 *
 * @parametrii: Materie - pointer la un pointer la materie
 * @return: 1 - daca distrugerea a avut loc
 *          0 - altfel
 */
bool DistrugeMaterie(MATERIE_P* Materie);

/*
 * functia afiseaza materia in format de tip: [Id: ; Nume ; Producator: ; Cantitate ;]
 *
 * @parametrii: Materie - o materie
 *
 * @return: -
 */
void PrintMaterie(MATERIE Materie);

/*
 * functia returneaza numele materiei prime
 *
 * @parametrii: Materie - o materie
 *
 * @return: numele materiei (char*)
 */
char*  GetNume(MATERIE Materie);

/*
 * functia returneaza producatorul materiei prime
 *
 * @parametrii: Materie - o materie
 *
 * @return: producatorul materiei (char*)
 */
char* GetProducator(MATERIE Materie);

/*
 * functia returneaza cantitatea materiei prime
 *
 * @parametrii: Materie - o materie
 *
 * @return: cantitatea materiei (integer)
 */
int GetCantitate(MATERIE Materie);

/*
 * functia seteaza Numele materiei prime
 *
 * @parametrii: Pointer la Materie - o materie
 *
 * @return: -
 */
void SetNume(MATERIE_P Materie, char *Nume);

/*
 * functia seteaza producatorul materiei prime
 *
 * @parametrii: Pointer la Materie - o materie
 *
 * @return: -
 */
void SetProducator(MATERIE_P Materie, char *Producator);

/*
 * functia seteaza cantitatea materiei prime
 *
 * @parametrii: Pointer Materie - o materie
 *
 * @return: -
 */
void SetCantitate(MATERIE_P Materie, int Cantitate);

/*
 * functia returneaza daca doua materii sunt egale sau nu
 * fiecare materie trebuie sa aiba un nume unic
 *
 * @parametrii: Materie1, Materie2 - materii prime
 *
 * @return: 1 - daca materiile sunt egale
 *          0 - altfel
 */
bool MateriiEgale(MATERIE Materie1, MATERIE Materie2);

bool ComparaCrescatorCantitate(MATERIE Materie1, MATERIE Materie2);
bool ComparaCrescatorNume(MATERIE Materie1, MATERIE Materie2);
bool ComparaDescrescatorCantitate(MATERIE Materie1, MATERIE Materie2);
bool ComparaDescrescatorNume(MATERIE Materie1, MATERIE Materie2);

#endif //PROBLEMA006_DOMAIN_H
