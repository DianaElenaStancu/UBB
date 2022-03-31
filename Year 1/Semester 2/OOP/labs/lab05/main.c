//
// Created by Diana-Elena Stancu on 26/03/2022.
//
#include "tests.h"
#include "ui.h"
#include <stdio.h>

int main() {
    RunAllTests();
    printf("Tests passed\n");

    ValidationFunction validator = ValidateCheltuiala;

    PREPOSITORY Repository = CreateRepository();

    SERVICE_CHELTUIELI service = CreateService(Repository, validator);

    CONSOLE console = CreateConsole(service);

    runConsole(&console);

    DestroyConsole(&console);

    //_CrtDumpMemoryLeaks();
}