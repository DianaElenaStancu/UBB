//
// Created by Diana-Elena Stancu on 15/03/2022.
//

#ifndef PROBLEMA006_SERVICE_H
#define PROBLEMA006_SERVICE_H

#include "repo.h"
#include "validator.h"
#include "repo.h"
#include "utils.h"
#include <stdlib.h>

typedef struct _SERVICE_MATERII {
    REPOSITORY_MATERII_P Repository;
    Validator ValidatorMaterie;
}SERVICE_MATERII, *SERVICE_MATERII_P;

/*
 * functia creeaza un service pentru materii
 *
 * @parametrii: Service - un pointer spre un pointer de service de materii
 *              Repository - un pointer spre un repo
 *              Validation - pointer la validator
 *
 * @return: 1 - daca crearea a avut succes
 *          0 - altfel
 */
bool CreeazaService(SERVICE_MATERII_P* Service, REPOSITORY_MATERII_P Repository, Validator ValidatorM);

/*
 * functia distruge service-ul
 *
 * @parametrii: Service - pointer spre un pointer de servicii de materii
 *
 * @return: 1 - daca distrugerea a avut loc
 *          0 - altfel
 */
bool DistrugeService(SERVICE_MATERII_P* Service);

/*
 * functia adauga o noua materie in repo
 *
 * @parametrii: Service - un pointer spre un Service
 *              Nume - un pointer la numele materiei (char*)
 *              Producator - un pointer la producatorul materiei (char*)
 *              Cantitate - cantitatea materiei (integer)
 *              erori - daca sunt erori se vor adauga la adresa specificata (char*)
 * @return: 1 - daca a fost adaugata cu succes materia
 *          0 - altfel
 */
bool AdaugaMaterieSRV(SERVICE_MATERII_P Service, char* Nume, char* Producator, int Cantitate, char* erori);

/*
 * functia sterge o materie din repo
 *
 * @parametrii: Service - un pointer spre un Service
 *              Nume - un pointer la numele materiei (char*)
 *              erori - daca sunt erori se vor adauga la adresa specificata (char*)
 * @return: 1 - daca a fost stearsa cu succes materia
 *          0 - altfel
 */
bool StergeMaterieSRV(SERVICE_MATERII_P Service, char* Nume, char* erori);

/*
 * functia modifica o materie din repo
 *
 * @parametrii: Service - un pointer spre un Service
 *              Nume - un pointer la numele materiei (char*)
 *              Producator - un pointer la producatorul materiei (char*)
 *              Cantitate - cantitatea materiei (integer)
 *              erori - daca sunt erori se vor adauga la adresa specificata (char*)
 * @return: 1 - daca a fost modificata cu succes materia
 *          0 - altfel
 */
bool ModificaMaterieSRV(SERVICE_MATERII_P Service, char* Nume, char* Producator, int Cantitate, char* erori);

/*
 * functia returneaza prin Array materiile care pot fi afisate
 *
 * @parametrii: Service - un pointer spre service
 *              optiune - optiunea vizulizarii
 *                      0 - vizualizare toata lista
 *                      1 - vizualizare dupa initiala unui nume
 *                      2 - vizualizare dupa cantitate
 *              filtru - filtrul vizualizarii
 *              Array - un pointer la sirul de materii
 *              len - lungimea array
 *              erori - un pointer la sirul de erori
 *
 * @return: 1 - daca nu sunt erori
 *          0 - altfel
 */
bool GetAllSRV(SERVICE_MATERII_P Service, int optiune, char filtru[], MATERIE_P* Array, int* len, char* erori);

/*
 * functia sorteaza materiile prime din repo
 *
 * @parametrii: Service - pointer spre service
 *              optiune - 0 - crescator dupa cantitate
 *                        1 - crescator dupa nume
 *                        2 - descrescator dupa cantitate
 *                        3 - descrescator dupa nume
 *              Array - pointer spre un array
 *              erori - pointer
 *
 * @return: 1 - daca sortarea a avut loc cu succes
 *          0 - altfel
 */
bool Sorteaza(SERVICE_MATERII_P Service, int optiune, MATERIE_P* Array, char* erori);
#endif //PROBLEMA006_SERVICE_H
