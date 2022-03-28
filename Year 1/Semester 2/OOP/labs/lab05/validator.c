//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "validator.h"

int ValidateCheltuiala(CHELTUIALA* Cheltuiala, char* errors)
{
    errors[0] = '\0';
    if (GetId(Cheltuiala) < 0) {
        strcat(errors, "Invalid id!\n");
    }
    if (GetNumarApartament(Cheltuiala) <= 0) {
        strcat(errors, "Invalid apartment number!\n");
    }
    if (GetSuma(Cheltuiala) <= 0) {
        strcat(errors, "Invalid sum!\n");
    }
    if (strlen(GetTip(Cheltuiala)) == 0)
    {
        strcat(errors, "Invalid type!\n");
    }

    if (strlen(errors) > 0)
    {
        return 0;
    }
    return 1;
}

void TestValidator() {
    CHELTUIALA* Cheltuiala = CreateCheltuiala(6, 1, 200.34, "apa");
    char* errors = (char*)malloc(sizeof (char) * 100);

    assert(ValidateCheltuiala(Cheltuiala, errors));
    assert(strlen(errors) == 0);
    DestroyCheltuiala(Cheltuiala);

    Cheltuiala = CreateCheltuiala(-2, 1, 200.34, "apa");
    assert(ValidateCheltuiala(Cheltuiala, errors) == 0);
    assert(strcmp(errors, "Invalid id!\n") == 0);
    DestroyCheltuiala(Cheltuiala);

    Cheltuiala = CreateCheltuiala(-2, 0, 200.34, "apa");
    assert(ValidateCheltuiala(Cheltuiala, errors) == 0);
    assert(strcmp(errors, "Invalid id!\nInvalid apartment number!\n") == 0);
    DestroyCheltuiala(Cheltuiala);

    Cheltuiala = CreateCheltuiala(-2, 0, -67.8, "apa");
    assert(ValidateCheltuiala(Cheltuiala, errors) == 0);
    assert(strcmp(errors, "Invalid id!\nInvalid apartment number!\nInvalid sum!\n") == 0);
    DestroyCheltuiala(Cheltuiala);

    Cheltuiala = CreateCheltuiala(-2, 0, -67.8, "");
    assert(ValidateCheltuiala(Cheltuiala, errors) == 0);
    assert(strcmp(errors, "Invalid id!\nInvalid apartment number!\nInvalid sum!\nInvalid type!\n") == 0);
    DestroyCheltuiala(Cheltuiala);

    free(errors);
}