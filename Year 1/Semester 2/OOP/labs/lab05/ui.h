//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#ifndef LAB05_UI_H
#define LAB05_UI_H
#include <stdio.h>
#include "ui.h"
#include "service.h"
#define _CRT_SECURE_NO_WARNINGS

typedef struct CONSOLE {
    SERVICE_CHELTUIELI ServiceCheltuieli;
} CONSOLE, * PCONSOLE;

int readCommand();

CONSOLE CreateConsole(SERVICE_CHELTUIELI ServiceCheltuieli);

void DestroyConsole(CONSOLE* Console);

static int consoleAddCheltuiala(PCONSOLE Console, char* errors);

static int consoleDeleteCheltuiala(PCONSOLE Console, char* errors);

int consoleModifyCheltuiala(PCONSOLE Console, char* errors);

static int consoleViewCheltuieli(PCONSOLE Console, char* errors);

static int consoleFilterCheltuieli(PCONSOLE Console, char* errors);

int consoleUndo(PCONSOLE Console, char* errors);

int runConsole(PCONSOLE Console);
#endif //LAB05_UI_H
