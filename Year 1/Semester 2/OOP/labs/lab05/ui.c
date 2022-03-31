//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "ui.h"

//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "ui.h"
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"

int readCommand()
{
    printf("Give a command: \n0 - Exit\n1 - Adauga cheltuiala\n2 - Sterge cheltuiala\n3 - Modifica cheltuiala\n4 - Vezi cheltuieli\n5 - Filtreaza cheltuieli\n6 - Undo\n");
    char strCommand[2];
    int command;
    if (scanf("%1s", strCommand) != 1)
    {
        return -1;
    }

    while ((command = getchar()) != '\n' && command != EOF);

    if (isInteger(strCommand) != 1)
    {
        return -1;
    }

    return atoi(strCommand);
}

CONSOLE CreateConsole(SERVICE_CHELTUIELI ServiceCheltuieli)
{
    CONSOLE console;

    console.ServiceCheltuieli = ServiceCheltuieli;

    return console;
}

void DestroyConsole(CONSOLE* Console)
{
    DestroyService(&(Console->ServiceCheltuieli));
}

static int consoleAddCheltuiala(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int id, numar_apartament;
    double suma;
    char *tip;

    tip = (char*)malloc(INPUT_SIZE * sizeof(char));

    if (tip == NULL)
    {
        free(tip);
        strcat(errors, "The adding failed!\n");
        return -1;
    }

    printf("Id: ");
    if (scanf("%d", &id) != 1)
    {
        free(tip);
        strcat(errors, "Invalid id!\n");
        return -1;
    }
    printf("Numar apartament: ");
    if (scanf("%d", &numar_apartament) != 1)
    {
        free(tip);
        strcat(errors, "Invalid numar apartament!\n");
        return -1;
    }
    printf("Sum: ");
    if (scanf("%lf", &suma) != 1)
    {
        free(tip);
        strcat(errors, "Invalid sum!\n");
        return -1;
    }
    printf("Type: ");
    if (scanf("%s", tip) != 1)
    {
        free(tip);
        strcat(errors, "Invalid type!\n");
        return -1;
    }
    else
    {
        if (strcmp(tip, "apa") != 0 && strcmp(tip, "gaz") != 0 && strcmp(tip, "canal") != 0 && strcmp(tip, "incalzire") != 0)
        {
            free(tip);
            strcat(errors, "Invalid type!\n");
            return -1;
        }
    }
    printf("\n");

    if (StoreCheltuiala(&(Console->ServiceCheltuieli), id, numar_apartament, suma, tip, errors) != 0)
    {
        free(tip);
        strcat(errors, "The adding failed!\n");
        return -1;
    }

    free(tip);

    return 0;
}

static int consoleDeleteCheltuiala(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int id;

    printf("Id: ");
    if (scanf("%d", &id) != 1)
    {
        strcat(errors, "Could not read the id!\n");
        return -1;
    }

    if (EraseCheltuiala(&(Console->ServiceCheltuieli), id, errors) != 0)
    {
        return -1;
    }

    return 0;
}

int consoleModifyCheltuiala(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int id, numar_apartament = -oo;
    double suma = -oo;

    char *tip;

    tip = (char*)malloc(INPUT_SIZE * sizeof(char));

    int modifyType;
    printf("0 - Modifica numar apartament\n1 - Modify suma\n2 - Modifica tip\n3 - Modifica tot\n");
    if (scanf("%d", &modifyType) != 1)
    {
        strcat(errors, "Could not read the cmd!\n");
        return -1;
    }

    if (modifyType != 0 && modifyType != 1 && modifyType != 2 && modifyType != 3)
    {
        strcat(errors, "Invalid command!\n");
        return -1;
    }

    printf("Id: ");
    if (scanf("%d", &id) != 1)
    {
        strcat(errors, "Could not read the id!\n");
        return -1;
    }

    if (modifyType == 1 || modifyType == 3)
    {
        printf("New suma: ");
        if (scanf("%lf", &suma) != 1)
        {
            strcat(errors, "Invalid sum!\n");
            return -1;
        }
    }

    if (modifyType == 0 || modifyType == 3)
    {
        printf("New numar apartament: ");
        if (scanf("%d", &numar_apartament) != 1)
        {
            strcat(errors, "Invalid numar apartament!\n");
            return -1;
        }
    }

    if (modifyType == 2 || modifyType == 3)
    {
        printf("Tip: ");
        if (scanf("%s", tip) != 1)
        {
            free(tip);
            strcat(errors, "Invalid type!\n");
            return -1;
        }
    }

    Console->ServiceCheltuieli;
    if (ChangeCheltuiala(&(Console->ServiceCheltuieli), id, numar_apartament, suma, tip, errors) != 0)
    {
        strcat(errors, "The changing failed!\n");
        return -1;
    }


    free(tip);
    return 0;
}

static int consoleViewCheltuieli(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int mode, ascMode;

    printf("0 - Dupa suma\n1 - Dupa tip\n");

    printf("Mode: ");
    if (scanf("%d", &mode) != 1)
    {
        strcat(errors, "Could not read the mode!\n");
        return -1;
    }

    printf("0 - Crescator\n1 - Descrescator\n");
    printf("Mode: ");
    if (scanf("%d", &ascMode) != 1)
    {
        strcat(errors, "Could not read the ascending mode!\n");
        return -1;
    }

    if ((mode != 0 && mode != 1) || (ascMode != 0 && ascMode != 1))
    {
        strcat(errors, "The mode must be 0 or 1!\n");
        return -1;
    }

    DYNAMIC_VECTOR * Array;

    Array = ViewCheltuieli(&(Console->ServiceCheltuieli), mode, ascMode, errors);

    int count = GetLength(Array);
    for (int i = 0; i < count; ++i)
    {
        TElem Cheltuiala = GetElement(Array, i);
        printf("Nr. apartament: %d\nSum: %lf\nType: %s\n\n", GetNumarApartament(Cheltuiala), GetSuma(Cheltuiala),
               GetTip(Cheltuiala));
    }

    if (count == 0)
    {
        printf("Nu exista cheltuieli!\n");
    }

    Destroy(Array, DestroyCheltuiala);

    return 0;
}

static int consoleFilterCheltuieli(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    double suma = 0;
    int numar_apartament = 0, mode = 0;
    char *tip;

    tip = (char*)malloc(INPUT_SIZE * sizeof(char));

    printf("0 - Filtreaza dupa numar apartament\n1 - Filtreaza dupa suma\n2 - Filtreaza dupa tip\n");

    if (scanf("%d", &mode) != 1)
    {
        free(tip);
        strcat(errors, "Invalid mode!\n");
        return -1;
    }
    if (mode != 0 && mode != 1 && mode != 2)
    {
        free(tip);
        strcat(errors, "Invalid mode!\n");
        return -1;
    }

    if (mode == 0)
    {
        printf("Nr. Apartament");
        if (scanf("%d", &numar_apartament) != 1)
        {
            free(tip);
            strcat(errors, "Invalid mode!\n");
            return -1;
        }
    }
    else if(mode == 1)
    {
        printf("Sum: ");
        if (scanf("%lf", &suma) != 1)
        {
            free(tip);
            strcat(errors, "Invalid sum!\n");
            return -1;
        }
    }
    else
    {
        printf("Tip: ");
        if (scanf("%s", &tip) != 1)
        {
            free(tip);
            strcat(errors, "Invalid sum!\n");
            return -1;
        }
    }

    DYNAMIC_VECTOR * Array;
    Array = FilterCheltuieli(&(Console->ServiceCheltuieli), numar_apartament, suma, tip, mode, errors);

    int count = GetLength(Array);
    for (int i = 0; i < count; ++i)
    {
        TElem Cheltuiala = GetElement(Array, i);
        printf("Nr. apartament: %d\nSum: %lf\nType: %s\n\n", GetNumarApartament(Cheltuiala), GetSuma(Cheltuiala),
               GetTip(Cheltuiala));
    }

    if (count == 0)
    {
        printf("Nu exista cheltuieli!\n");
    }

    free(tip);
    Destroy(Array, DestroyCheltuiala);
    return 0;
}

int consoleUndo(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    if (Undo(&(Console->ServiceCheltuieli)) != 0)
    {
        strcat(errors, "No more undos!\n");
        return -1;
    }
    return 0;
}

int runConsole(PCONSOLE Console)
{
    if (Console == NULL)
    {
        return -1;
    }

    char* errors = (char*)malloc(100 * sizeof(char));
    if (errors == NULL)
    {
        return -1;
    }

    while (1)
    {
        int command = readCommand();
        int returnValue = 0;
        if (command == 0)
        {
            break;
        }
        else if (command == 1)
        {
            returnValue = consoleAddCheltuiala(Console, errors);
        }
        else if (command == 2)
        {
            returnValue = consoleDeleteCheltuiala(Console, errors);
        }
        else if (command == 3)
        {
            returnValue = consoleModifyCheltuiala(Console, errors);
        }
        else if (command == 4)
        {
            returnValue = consoleViewCheltuieli(Console, errors);
        }
        else if (command == 5)
        {
            returnValue = consoleFilterCheltuieli(Console, errors);
        }
        else if (command == 6)
        {
            returnValue = consoleUndo(Console, errors);
        }
        else
        {
            printf("Invalid command!\n");
            continue;
        }

        if (returnValue != 0)
        {
            while ((command = getchar()) != '\n' && command != EOF);
            printf("%s", errors);
        }
        printf("\n");
    }

    free(errors);

    return 0;
}
