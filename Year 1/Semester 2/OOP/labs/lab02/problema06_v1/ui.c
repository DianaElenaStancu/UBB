//
// Created by Diana-Elena Stancu on 05/03/2022.
//

#include "ui.h"
#include "service.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

Ui createUi(Service srv) {
    /*
     * creeaza un struct de tip Ui
     * primeste ca parametru srv de tip Service
     */
    Ui ui;
    ui.srv = srv;
    return ui;
}


void printMenu() {
    printf("----------\n");
    printf("0. Exit\n");
    printf("1. Add raw material\n");
    printf("2. Update raw material\n");
    printf("3. Delete raw material\n");
    printf("4. See raw materials by option\n");
    printf("5. Sort raw materials by option\n");
    printf("6. Print all\n");
    printf("----------\n");
}

void addUi(Ui ui) {
    char name[20], producer[20];
    int quantity;
    printf("Adaugati materie prima sub forma: nume producator cantitate -> ");
    int len;
    len = scanf("%s %s %d", name, producer, &quantity);
    if (len < 3) {
        printf("Materia prima nu a putut fi adaugata.\n");
        return;
    }

    bool succ = addMaterieSrv(&ui.srv, name, producer, quantity);
    if (succ == false)
        printf("Materia prima nu a putut fi adaugata.\n");
    else
        printf("Materia prima adaugata cu succes!\n");
}
void printAllUi(Ui ui) {
    printf("Toate materialele prime din cofetarie sunt: \n");
    Materie* materie = getRepoSrv(&ui.srv);
    int len = getLenRepo(&ui.srv);
    printUi(materie, len);
}

void printUi(Materie* materie, int len) {
    printf("**********\n");
    if (len == 0) {
        printf("nu sunt materiale prime in cofetarie :(\n");
        printf("**********\n");
        return;
    }
    for (int i = 0; i < len; i++) {
        printf("Materie %d: [%s] \n", i, str(materie[i]));
    }
    printf("**********\n");
}

void updateUi(Ui ui) {
    int len = getLenRepo(&ui.srv);
    if (len == 0) {
        printf("nu sunt materii prime in repo!\n");
        return;
    }

    char name[20], producer[20];
    int quantity;
    printf("Updatati materie prima sub forma: nume producator cantitate -> ");
    scanf("%s %s %d", name, producer, &quantity);

    bool succ = updateMaterieSrv(&ui.srv, name, producer, quantity);
    if (succ == false)
        printf("Materia prima nu a putut fi updata.\n");
    else
        printf("Materia prima updatata cu succes!\n");
}

void deleteUi(Ui ui) {
    int len = getLenRepo(&ui.srv);
    if (len == 0) {
        printf("nu sunt materii prime in repo!\n");
        return;
    }

    char name[20];
    printf("Stergeti materia cu numele -> ");
    scanf("%s", name);

    bool succ = deleteMaterieSrv(&ui.srv, name);
    if (succ == false)
        printf("Materia prima nu a putut fi stearsa.\n");
    else
        printf("Materia prima stearsa cu succes!\n");
}

void printByOption(Ui ui) {
    printf("............\n");
    printf ("Optiuni de filtrare:\n");
    printf ("a. nume: afisarea tuturor materiilor prime care incep cu o litera data\n");
    printf ("b. productor: afisarea tuturor materiilor prime care au un producator dat\n");
    printf ("c. cantitate: afisarea tuturor materiilor prime care au cantitatea mai mica decat cea data\n");
    printf("............\n");
    printf("Optiune filtrare (a,b,c) -> ");
    char cmd;
    MateriiRepo materieFiltered;
    scanf(" %c", &cmd);
    if (cmd == 'a') {
        char l;
        printf("Litera cu care sa inceapa numele produsului -> ");
        scanf(" %c", &l);
        materieFiltered = filterByName(&ui.srv, l);
    } else if (cmd == 'b') {
        char producer[30];
        printf("Producator produs -> ");
        scanf(" %s", producer);
        materieFiltered = filterByProducer(&ui.srv, producer);
    } else if (cmd == 'c') {
        int quantity;
        printf("Cantitate produs -> ");
        scanf(" %d", &quantity);
        materieFiltered = filterByQuantity(&ui.srv, quantity);
    } else {
        printf ("Comanda inexistenta!\n");
        printByOption(ui);
    }
    //afisam materia filtrata
    printUi(materieFiltered.repo, materieFiltered.len);
}

void run(Ui ui) {
    //the console for user interaction
    bool running = true;
    char* cmd;

    while (running) {
        printMenu();
        printf("The command (0,1,..) -> ");
        scanf("%s", cmd);
        if (strcmp(cmd, "0") == 0) {
            running = false;
        } else if (strcmp(cmd, "1") == 0) {
            addUi(ui);
        } else if (strcmp(cmd, "2") == 0) {
            updateUi(ui);
        } else if (strcmp(cmd, "3") == 0) {
            deleteUi(ui);
        } else if (strcmp(cmd, "4") == 0) {
            printByOption(ui);
        } else if (strcmp(cmd, "6") == 0) {
            printAllUi(ui);
        } else {
            printf("Invalid command\n");
        }

    }
}
