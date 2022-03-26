//
// Created by Diana-Elena Stancu on 05/03/2022.
//

#include "domain.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

Materie createMaterie (char* name, char* producer, int quantity) {
    /*
     * creeaza un struct de tip Materie alocat dinamic
     * nume: sir de caractere nevid
     * producator: sir de caractere nevid
     * cantitate: int > 0
     * returneaza un struct de tip Materie
     */
    Materie material;
    size_t nrC = strlen(name) + 1;
    material.name = (char*)malloc(sizeof(char) * nrC);
    strcpy(material.name, name);
    nrC = strlen(producer) + 1;
    material.producer = (char*)malloc(sizeof(char) * nrC);
    strcpy(material.producer, producer);
    material.quantity = quantity;
    return material;
}

char* getName(Materie *materie) {
    return materie->name; //echivalent cu (*materie).name
}

char* getProducer(Materie *materie) {
    return materie->producer;
}

int getQuantity(Materie *materie) {
    return materie->quantity;
}

void setName(Materie *material, char* name) {
    if (strcmp(name, "") == 0) return;
    free(material -> name);
    material->name = NULL;
    size_t nrC = strlen(name) + 1;
    material->name = malloc(sizeof(char) * nrC);
    strcpy(material -> name, name);
}

void setProducer(Materie *materie, char* producer) {
    if (strcmp(producer, "") == 0) return;
    free(materie -> producer);
    materie -> producer = NULL;
    size_t nrC = strlen(producer) + 1;
    materie -> producer = malloc(sizeof(char) * nrC);
    strcpy(materie -> producer, producer);
}

void setQuantity(Materie *materie, int quantity) {
    materie -> quantity = quantity;
}

bool equal(Materie materie1, Materie materie2) {
    /*
     * verifica daca 2 materii prime sunt egale
     * 2 materii sunt egale daca au acelasi nume
     */
    if (strcmp(materie1.name, materie2.name) == 0) return 1;
    return 0;
}

void destroyMaterie(Materie* materie) {
    /*
     * dealoca spatiul ocupat de materie
     * seteaza pointerii la NULL
     */
    free(materie->name);
    materie->name = NULL;
    free(materie->name);
    materie->producer = NULL;
}

char* str(Materie materie) {
    /*
     *  reprezinta datele unui materie sub forma:
     *  nume:...; producator:...; cantitate:...
     *  intr-un singur string
     */
    char* materieStr;
    int nrC = strlen(materie.name) + strlen(materie.producer) + 50;
    materieStr = (char*)malloc(sizeof(char) * nrC);
    materieStr[0] = '\0';
    strcat(materieStr, "nume: ");
    strcat(materieStr, getName(&materie));
    strcat(materieStr, "; producator: ");
    strcat(materieStr, getProducer(&materie));
    strcat(materieStr, "; cantitate: ");
    char quantity[10];
    sprintf(quantity,"%d" ,getQuantity(&materie));
    strcat(materieStr, quantity);
    return materieStr;
}

Materie copy(Materie materie) {
    Materie c = createMaterie(getName(&materie), getProducer(&materie), getQuantity(&materie));
    return c;
}