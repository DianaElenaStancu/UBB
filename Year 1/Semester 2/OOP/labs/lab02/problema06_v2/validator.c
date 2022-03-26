//
// Created by Diana-Elena Stancu on 14/03/2022.
//

#include "validator.h"

bool ValideazaMaterie(MATERIE Materie, char* erori) {
    erori[0] = '\0';
    if (strlen(Materie.Nume) == 0)
        strcat(erori, "Nume invalid\n");
    if (strlen(Materie.Producator) == 0)
        strcat(erori, "Producator invalid\n");
    if (Materie.Cantitate <= 0)
        strcat(erori, "Cantitate invalida\n");

    if (strlen(erori) > 0)
        return 0;
    return 1;
}