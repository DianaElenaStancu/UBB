//
// Created by Diana-Elena Stancu on 05/03/2022.
//

#ifndef PROBLEMA06_DOMAIN_H
#define PROBLEMA06_DOMAIN_H

#include <stdbool.h>

typedef struct {
    char* name;
    char* producer;
    int* quantity;
} Materie;

Materie createMaterie (char* name, char* producer, int quantity);
char* getName(Materie *materie);
char* getProducer(Materie *materie);
int getQuantity(Materie *materie);
void setName(Materie *material, char* name);
void setProducer(Materie *materie, char* producer);
void setQuantity(Materie *materie, int quantity);
bool equal(Materie materie1, Materie materie2);
void destroyMaterie(Materie *materie);
char* str(Materie materie);
Materie copy(Materie materie);


#endif //PROBLEMA06_DOMAIN_H
