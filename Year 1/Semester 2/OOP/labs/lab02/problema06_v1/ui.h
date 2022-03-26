//
// Created by Diana-Elena Stancu on 05/03/2022.
//
#include "service.h"
#ifndef PROBLEMA06_UI_H
#define PROBLEMA06_UI_H

typedef struct {
    Service srv;
} Ui;

Ui createUi(Service srv);
void run();
void addUi(Ui ui);
void printUi(Materie* materie,int len);
void printAllUi(Ui ui);
#endif //PROBLEMA06_UI_H
