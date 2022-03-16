//
// Created by Diana-Elena Stancu on 14/03/2022.
//

#include "tests.h"
#include "ui.h"

int main() {
    runTests(); //with coverage
    printf("Tests passed :)");

    Validator validator = ValideazaMaterie;
    REPOSITORY_MATERII_P repository;
    if (CreeazaRepository(&repository) == 0)
        exit(-1);
    SERVICE_MATERII_P service;
    if (CreeazaService(&service, repository, validator) == 0) {
        DistrugeRepository(&repository);
        exit(-1);
    }
    UI_P console;
    if (CreeazaUI(&console, service) == 0) {
        if (DistrugeService(&service) == 0)
            DistrugeRepository(&repository);
        exit(-1);
    }

    runUI(console);

}