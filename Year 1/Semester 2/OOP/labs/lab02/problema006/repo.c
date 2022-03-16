//
// Created by Diana-Elena Stancu on 14/03/2022.
//
#include "repo.h"

bool CreeazaRepository(REPOSITORY_MATERII_P* Repository) {
    if (Repository == NULL) return 0;

    REPOSITORY_MATERII_P r = (REPOSITORY_MATERII_P)malloc(sizeof(REPOSITORY_MATERII));
    if (r == NULL) return 0;

    MATERIE_P *a = (MATERIE_P*)malloc(sizeof(MATERIE)*INIT_SIZE);
    if (a == NULL) return 0;

    r->Array = a;
    r->Capacitate = INIT_SIZE;
    r->Lungime = 0;

    *Repository = r;
    return 1;
}

bool DistrugeRepository(REPOSITORY_MATERII_P* Repository) {
    if (Repository == NULL)
        return 0;
    while (GetLungimeREPO(*Repository) > 0) {
        if (StergeMaterieREPO(*Repository, *((*Repository)->Array[0])) == 0) return 0;
    }
    free((*Repository)->Array);
    free(*Repository);
    *Repository = NULL;
    return 1;
}

bool RedimRepository(REPOSITORY_MATERII_P Repository) {
    // cazul in care trebuie marita capacitatea repo-ului
    bool mod = 0;
    if (Repository->Capacitate == Repository->Lungime) {
        Repository->Capacitate = Repository->Capacitate * 2;
        mod = 1;
    } else if (Repository->Capacitate > INIT_SIZE && Repository->Capacitate / Repository->Lungime > 2) {
        Repository->Capacitate = Repository->Capacitate / 2;
        mod = 1;
    }
    if (mod) {
        MATERIE_P *a = (MATERIE_P *) malloc(sizeof(MATERIE *) * Repository->Capacitate);
        if (a == NULL) return 0;
        for (int i = 0; i < Repository->Lungime; i++)
            a[i] = Repository->Array[i];
        free(Repository->Array);
        Repository->Array = a;
    }
    return 1;
}

int GetLungimeREPO(REPOSITORY_MATERII_P Repository) {
    return (*Repository).Lungime;
}

bool GetAll(REPOSITORY_MATERII_P Repository, MATERIE_P* Array) {
    if (Repository == NULL || Array == NULL)
        return 0;

    int len = GetLungimeREPO(Repository);
    MATERIE_P a = (MATERIE_P) malloc(sizeof(MATERIE) * len);
    if (a == NULL) return 0;

    for (int i = 0; i < len; i++)
        a[i] = *(Repository->Array[i]);

    *Array = a;
    return 1;
}

bool StergeMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE Materie) {
    bool success = 0;
    for (int i = 0; i < Repository->Lungime; i++) {
        if (MateriiEgale(*(Repository->Array[i]), Materie)) {
            DistrugeMaterie(&(Repository->Array[i]));
            for (int j = i; j < Repository->Lungime - 1; j++) {
                Repository->Array[j] = Repository->Array[j + 1];
            }
            success = 1;
            Repository->Lungime -= 1;
            break;
        }
    }
    RedimRepository(Repository);
    return success;
}

bool AdaugaMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE_P Materie) {
    int poz = CautaMaterieREPO(Repository, *Materie);
    if (poz != -1) {
        int c = GetCantitate(*Materie);
        SetCantitate(Repository->Array[poz], c);
        return 1;
    }
    RedimRepository(Repository);
    Repository->Array[Repository->Lungime] = Materie;
    Repository->Lungime += 1;
    return 1;
}

bool ModificaMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE_P Materie) {
    if (Repository == NULL) return 0;
    if (Materie == NULL) return 0;
    int poz = CautaMaterieREPO(Repository, *Materie);
    if (poz == -1)
        return 0;
    Repository->Array[poz] = Materie;
    return 1;
}

int CautaMaterieREPO(REPOSITORY_MATERII_P Repository, MATERIE Materie) {
    for (int i = 0; i < Repository->Lungime; i++) {
        if (MateriiEgale(Materie, *(Repository->Array[i])))
            return i;
    }
    return -1;
}
