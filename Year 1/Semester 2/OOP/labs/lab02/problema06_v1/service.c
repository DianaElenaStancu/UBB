//
// Created by Diana-Elena Stancu on 06/03/2022.
//
#include <stdio.h>
#include <string.h>
#include "service.h"
#include "repo.h"
#include "validator.h"

Service createService(MateriiRepo repo){
    Service service;
    service.repo = repo;
    return service;
}

void destroyService(Service* service) {
    //distruge repo
    destroyRepo(&service->repo);
}

bool addMaterieSrv(Service* service, char* name, char* producer, int quantity) {
    /*
     * creeaza o instanta de tip Materie
     * si o adauga in repo
     * apoi distruge materialul
     * name: numele produsului, de tip char nevid
     * producer: numele producatorului, de tip char nevid
     * quantity: cantitatea produsului de tip int > 0
     */
    Materie material = createMaterie(name, producer, quantity);
    bool succ = validate(&material);
    if (succ == false) return false;
    succ = addMaterie(&(*service).repo, material);
    if (succ == false) return false;
    destroyMaterie(&material);
    return true;
}
bool updateMaterieSrv(Service* service, char* name, char* producer, int quantity) {
    /*
     * updateaza materia prima identificata prin numele sau unic
     * daca producatorul sau cantitatea nu sunt valide
     * nu o sa se poata updata materia prima
     */
    Materie newMaterie = createMaterie(name, producer, quantity);
    bool succ = validate(&newMaterie);
    if (succ == false) return false;
    succ = updateMaterie(&(*service).repo, newMaterie);
    if (succ == false) return false;
    destroyMaterie(&newMaterie);
    return true;
}

bool deleteMaterieSrv(Service* service, char* name) {
    /*
     * sterge materia identificata prin numele sau unic
     * daca materia nu exista in repo atunci se va semnala greseala
     */
    Materie materie = createMaterie(name, "a", 1);
    bool succ = validate(&materie);
    if (succ == false) return false;
    succ = deleteMaterie(&(*service).repo, materie);
    if (succ == false) return false;
    destroyMaterie(&materie);
    return true;
}

MateriiRepo filterByName(Service* service, char l) {
    /*
     * trece prin toate produsele si formeaza
     * un nou vector alocat dinamic cu toate produsele
     * in care numele incepe cu initiala data de utilizator
     * service: service-ul aplicatiei
     * l: caracter introdus de utilizator
     * returneaza vectorul alocat dinamic cu produsele cu proprietatea data
     */
    MateriiRepo materiiFiltered = createRepo();
    Materie* materie = getRepo(service->repo);

    int len = getLen(service->repo), k = 0;
    for (int i = 0; i < len; i++) {
        if (getName(&materie[i])[0] == l) {
            (materiiFiltered.len) += 1;
            (materiiFiltered.repo)[(materiiFiltered.len) - 1] = copy(materie[i]);
        }
    }
    return materiiFiltered;
}

MateriiRepo filterByProducer(Service* service, char producer[]) {
    /*
     * trece prin toate produsele si formeaza
     * un nou vector alocat dinamic cu toate produsele
     * in care numele incepe cu initiala data de utilizator
     * service: service-ul aplicatiei
     * l: caracter introdus de utilizator
     * returneaza vectorul alocat dinamic cu produsele cu proprietatea data
     */
    MateriiRepo materiiFiltered = createRepo();
    Materie* materie = getRepo(service->repo);

    int len = getLen(service->repo), k = 0;
    for (int i = 0; i < len; i++) {
        if (strcmp(getProducer(&materie[i]), producer) == 0) {
            materiiFiltered.len += 1;
            (materiiFiltered.repo)[materiiFiltered.len - 1] = copy(materie[i]);
        }
    }
    return materiiFiltered;
}

MateriiRepo filterByQuantity(Service* service, int quantity) {
    /*
     * trece prin toate produsele si formeaza
     * un nou vector alocat dinamic cu toate produsele
     * in care numele incepe cu initiala data de utilizator
     * service: service-ul aplicatiei
     * l: caracter introdus de utilizator
     * returneaza vectorul alocat dinamic cu produsele cu proprietatea data
     */
    MateriiRepo materiiFiltered = createRepo();
    Materie* materie = getRepo(service->repo);

    int len = getLen(service->repo), k = 0;
    for (int i = 0; i < len; i++) {
        if (getQuantity(&materie[i]) <= quantity) {
            materiiFiltered.len += 1;
            (materiiFiltered.repo)[materiiFiltered.len - 1] = copy(materie[i]);
        }
    }
    return materiiFiltered;
}

Materie* getRepoSrv(Service* service) {
    return getRepo(service->repo);
}

int getLenRepo(Service* service) {
    return getLen(service->repo);
}