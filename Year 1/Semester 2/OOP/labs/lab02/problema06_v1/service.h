//
// Created by Diana-Elena Stancu on 06/03/2022.
//
#include "repo.h"
#ifndef PROBLEMA06_SERVICE_H
#define PROBLEMA06_SERVICE_H
typedef struct {
    MateriiRepo repo;
} Service;

Service createService(MateriiRepo repo);
void destroyService(Service* service);
Materie* getRepoSrv(Service* service);
int getLenRepo(Service* service);
bool addMaterieSrv(Service* service, char* name, char* producer, int quantity);
bool updateMaterieSrv(Service* service, char* name, char* producer, int quantity);
bool deleteMaterieSrv(Service* service, char* name);
MateriiRepo filterByName(Service* service, char l);
MateriiRepo filterByProducer(Service* service, char producer[]);
MateriiRepo filterByQuantity(Service* service, int quantity);

#endif //PROBLEMA06_SERVICE_H
