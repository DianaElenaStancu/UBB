//
// Created by Diana-Elena Stancu on 06/03/2022.
//
#include "domain.h"
#ifndef PROBLEMA06_REPO_H
#define PROBLEMA06_REPO_H
typedef struct {
    Materie* repo;
    int len;
    int capacity;
} MateriiRepo;

MateriiRepo createRepo();
void destroyRepo(MateriiRepo* materiiRepo);
bool addMaterie(MateriiRepo* materiiRepo, Materie materie);
int getLen(MateriiRepo materiiRepo);
Materie* getRepo (MateriiRepo materiiRepo);
void redim(MateriiRepo* materiiRepo);
int findMaterie (MateriiRepo* materiiRepo, Materie materie);
bool updateMaterie(MateriiRepo* materiiRepo, Materie newMaterie);
bool deleteMaterie(MateriiRepo* materiiRepo, Materie materie);

#endif //PROBLEMA06_REPO_H
