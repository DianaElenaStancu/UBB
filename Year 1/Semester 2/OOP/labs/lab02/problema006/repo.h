//
// Created by Diana-Elena Stancu on 14/03/2022.
//

#ifndef PROBLEMA006_REPO_H
#define PROBLEMA006_REPO_H
#include "domain.h"
#include <stdbool.h>
#define INIT_SIZE 2

typedef struct _REPOSITORY_MATERII {
    MATERIE_P* Array;
    int Lungime;
    int Capacitate;
}REPOSITORY_MATERII, *REPOSITORY_MATERII_P;

/*
 * functia creeaza un repository de materii
 *
 * @parametrii: Repository - un pointer la un pointer de materii
 *
 * @return: 1 - daca repositoryul a fost creat cu succes
 *          0 - in caz contrar
 */
bool CreeazaRepository(REPOSITORY_MATERII_P* Repository);

/*
 * functia distruge repository-ul de materii creat
 *
 * @parametrii: Repository - un pointer la un pointer de materii
 *
 * @return: 1 - daca repositoryul a fost distrus cu succes
 *          0 - altfel
 */
bool DistrugeRepository(REPOSITORY_MATERII_P* Repository);

/*
 * functia redimensioneaza Repo-ul (creste sau scade dimensiunea)
 * functia este apelata doar in cadrul functiilor de stergere si inserare Materie
 *
 * @parametrii: Repository - pointer la Repo
 *
 * @return: 1 - daca redimensionare a avut loc
 *          0 - altfel
 */
bool RedimRepository(REPOSITORY_MATERII_P Repository);

/*
 * functia returneaza cate materii sunt in repo
 *
 * @parametrii: Repository - un pointer la repositoryul cu materii
 *
 * @return: numarul de materii stocate in repo (integer)
 */
int GetLungimeREPO(REPOSITORY_MATERII_P Repository);

/*
 * functia returneaza un deep copy al materiile prime din repo
 *
 * @parametrii: Repository - un pointer spre un repo
 *              Array - pointer la un pointer de materii prime
 *
 * @return: 1 - daca procesul de deep copy a fost creat cu succes
 *          0 - altfel
 */
bool GetAll(REPOSITORY_MATERII_P Repository, MATERIE_P* Array);

/*
 * functia sterge o materie din Repo
 *
 * @parametrii: Repository - un pointer la Repo
 *              Materie - MATERIE
 *
 * @return: 1 - daca stergerea a avut loc
 *          0 - altfel
 */
bool StergeMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE Materie);

/*
 * functia insereaza o materie in repo si updateaza capacitatea repo-ului daca este nevoie
 *
 * @parametrii: Repository - pointer la un Repo de materii
 *              Materie - pointer la Materie
 * @return: 1 - daca inserarea a avut loc
 *          0 - altfel
 */
bool AdaugaMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE_P Materie);

/*
 * functie care cauta o Materie in Repo
 *
 * @parametrii: Repository: un pointer la Repo
 *              Materie: o materie
 *
 * @return: pozitia pe care se afla in array materia prima cautata
 *          -1 daca nu se gaseste materia in repo
 */
int CautaMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE Materie);

/*
 * functia modifca o materie din repo
 *
 * @parametrii: Repository: un pointer la Repo
 *              Materie: o materie
 * @return: 1 - daca materia a fost modificata cu succes
 *          0 - altfel
 */
bool ModificaMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE_P Materie);

#endif //PROBLEMA006_REPO_H
