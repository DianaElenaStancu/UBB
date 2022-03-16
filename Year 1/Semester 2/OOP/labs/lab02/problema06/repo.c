//
// Created by Diana-Elena Stancu on 06/03/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "repo.h"

MateriiRepo createRepo() {
    /*
     * creeaza un struct de tip repo de materii prime alocat dinamic
     * initializeaza un sir static de materii prime vide
     * lungimea = 0
     * capacitatea = 2
     * returneaza un struct repo de materii prime
     */
    MateriiRepo materialRepo;
    materialRepo.len = 0;
    materialRepo.capacity = 100;
    Materie* ptr = malloc(materialRepo.capacity * sizeof(Materie));
    materialRepo.repo = ptr;
    return materialRepo;
}

void destroyRepo(MateriiRepo* materiiRepo) {
    /*
     * dealoca spatiul ocupat de repo
     * seteaza toti pointerii la NULL
     */
    for (int i = 0; i < materiiRepo->len; i++)
        destroyMaterie(&materiiRepo->repo[i]);
    free(materiiRepo->repo);
    materiiRepo->repo = NULL;
}

Materie* getRepo (MateriiRepo materialRepo) {
    return materialRepo.repo;
}

int getLen(MateriiRepo materiiRepo) {
    return materiiRepo.len;
}
/*
void redim(MateriiRepo* materiiRepo) {

     * redimensioneaza repo
     * daca capacitatea repoului nu este suficienta
     * aloca mai mult spatiu (il dubleaza)

    if (*materiiRepo->len < *materiiRepo->capacity) {
        return;
    }
    else {
        int newCapacity = *materiiRepo->capacity * 2;
        Materie * newRepo = (Materie*)malloc(sizeof(Materie*) * newCapacity);
        for (int i = 0; i < *materiiRepo->len; i++) {
            newRepo[i] = copy(materiiRepo->repo[i]);
        }
        free(materiiRepo->repo);
        materiiRepo->repo = newRepo;
        *materiiRepo->capacity = newCapacity;
    }

}
void redim(MateriiRepo* materiiRepo) {
    if (*materiiRepo->len < *materiiRepo->capacity) {
        return;
    }
    else {
        int newCapacity = *materiiRepo->capacity * 2;
        Materie * new_arr = malloc(sizeof (Materie) * newCapacity);
        *(*materiiRepo).capacity = newCapacity;
        for(int i=0; i<  *(*materiiRepo).len; i++){
            Materie materie = copy(materiiRepo->repo[i]);
            new_arr[i] = materie;
        }
        free(materiiRepo->repo);
        materiiRepo->repo = new_arr;
    }
}
*/
int findMaterie (MateriiRepo* materiiRepo, Materie materie) {
    int i;
    for (i = 0; i < materiiRepo->len; i++) {
        if (equal(materiiRepo->repo[i], materie)) {
            return i;
        }
    }
    return -1;
}

bool addMaterie(MateriiRepo* materiiRepo, Materie materie) {
    /*
     * adauga materie prima in repo
     * daca materia prima deja exista
     * aceasta nu va fi adaugata
     */
    //printf("capacitatea este: %d\n", *materiiRepo->capacity);
    if (findMaterie(materiiRepo, materie) == -1) {
        //redim(materiiRepo);
        (*materiiRepo).len += 1;
        (*materiiRepo).repo[(*materiiRepo).len - 1] = copy(materie);
    } else {
        printf("Materia deja exista! Se updateaza cantitatea si producatorul acesteia.\n");
        updateMaterie(materiiRepo, materie);
        return false;
    }
    return true;
}

bool updateMaterie(MateriiRepo* materiiRepo, Materie newMaterie) {
    /*
     * updateaza materia prima identificata prin numele sau unic daca exista
     */
    int index = findMaterie(materiiRepo, newMaterie);
    if (index != -1)
        (*materiiRepo).repo[index] = copy(newMaterie);
    else {
        printf ("Materia prima cu numele dat nu exista in repo!\n");
        return false;
    }
    return true;
}

bool deleteMaterie(MateriiRepo* materiiRepo, Materie materie) {
    /*
     * sterge materia prima daca exista
     */
    int index = findMaterie(materiiRepo, materie);
    if (index != -1) {
        for (int i = index; i < materiiRepo->len - 1; i++) {
           // char name[30], producer[30]; int quantity;
            //strcpy(name, getName(&materiiRepo->repo[i+1]));
            //strcpy(producer, getProducer(&materiiRepo->repo[i+1]));
           // quantity = getQuantity(&materiiRepo->repo[i+1]);
            setName(&materiiRepo->repo[i], getName(&materiiRepo->repo[i+1]));
            setProducer(&materiiRepo->repo[i], getProducer(&materiiRepo->repo[i+1]));
            setQuantity(&materiiRepo->repo[i], getQuantity(&materiiRepo->repo[i+1]));

        }
        materiiRepo->len -= 1;
        destroyMaterie(&materiiRepo->repo[materiiRepo->len]);
    }
    else {
        printf ("Materia prima cu numele dat nu exista in repo!\n");
        return false;
    }
    return true;
}
