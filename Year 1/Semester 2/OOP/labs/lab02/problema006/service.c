//
// Created by Diana-Elena Stancu on 15/03/2022.
//

#include "service.h"

bool CreeazaService(SERVICE_MATERII_P* Service, REPOSITORY_MATERII_P Repository, Validator ValidatorM) {
    if (Service == NULL || Repository == NULL || ValidatorM == NULL)
    {
        if (Repository != NULL)
            DistrugeRepository(&Repository);
        return 0;
    }

    SERVICE_MATERII_P s = (SERVICE_MATERII_P)malloc(sizeof (SERVICE_MATERII));
    s->Repository = Repository;
    s->ValidatorMaterie = ValidatorM;

    *Service = s;
    return 1;
}

bool DistrugeService(SERVICE_MATERII_P* Service) {
    if (Service == NULL) return 0;
    REPOSITORY_MATERII_P r = (*Service)->Repository;
    DistrugeRepository(&r);
    free(*Service);
    *Service = NULL;
    return 1;
}

bool AdaugaMaterieSRV(SERVICE_MATERII_P Service, char* Nume, char* Producator, int Cantitate, char* erori) {
    if (erori == NULL) return 0;
    erori[0] = '\0';
    if (Service == NULL || Nume == NULL || Producator == NULL) {
        strcat(erori, "parametrii invalizi!\n");
        return 0;
    }
    MATERIE_P Materie;
    CreeazaMaterie(&Materie, Nume, Producator, Cantitate);
    if (Service->ValidatorMaterie(*Materie, erori) == 0) {
        DistrugeMaterie(&Materie);
        return 0;
    }
    bool success = AdaugaMaterieREPO(Service->Repository, Materie);
//    if (!success) {
//        strcat(erori, "materia nu a putut fi adaugata!\n");
//        return 0;
//    }
    //DistrugeMaterie(&Materie);
    return 1;
}

bool StergeMaterieSRV(SERVICE_MATERII_P Service, char* Nume, char* erori){
    if (erori == NULL) return 0;
    erori[0] = '\0';
    if(Service ==  NULL || Nume == NULL) {
        strcat(erori, "Parametrii invalizi!\n");
        return 0;
    }
    MATERIE_P Materie;
    CreeazaMaterie(&Materie, Nume, "", 0);
    int poz = CautaMaterieREPO(Service->Repository, *Materie);
    MATERIE_P* Array;
    bool success = StergeMaterieREPO(Service->Repository, *Materie);
    if (!success) {
        strcat(erori, "Materia nu exista in repo!\n");
        return 0;
    }
    return 1;
}

bool ModificaMaterieSRV(SERVICE_MATERII_P Service, char* Nume, char* Producator, int Cantitate, char* erori) {
    if (erori == NULL) return 0;
    erori[0] = '\0';
    if (Service == NULL || Nume == NULL || Producator == NULL) {
        strcat(erori, "parametrii invalizi!\n");
        return 0;
    }
    MATERIE_P Materie;
    CreeazaMaterie(&Materie, Nume, Producator, Cantitate);
    if (Service->ValidatorMaterie(*Materie, erori) == 0) {
        strcat(erori, "Modificarea nu poate avea loc, parametrii invalizi!\n");
        DistrugeMaterie(&Materie);
        return 0;
    }
    bool success = ModificaMaterieREPO(Service->Repository, Materie);
    if (!success) {
        strcat(erori, "Materia nu a putut fi modificata.\n");
        return 0;
    }
    return 1;
}

bool GetAllSRV(SERVICE_MATERII_P Service, int optiune, char filtru[], MATERIE_P* Array, int* len, char* erori) {
    if (erori == NULL) return 0;
    erori[0] = '\0';
    if (Service == NULL || Array == NULL) {
        strcat(erori, "parametrii invalizi!\n");
        return 0;
    }
    int lenRepo = GetLungimeREPO(Service->Repository);
    if (lenRepo == 0) {
        strcat(erori, "Nu exista materii prime in cofetarie!\n");
        return 0;
    }
    MATERIE_P a, b;
    a = (MATERIE_P) malloc(sizeof(MATERIE) * lenRepo);
    b = (MATERIE_P) malloc(sizeof(MATERIE) * lenRepo);
    GetAll(Service->Repository, &a);
    if (optiune == 0) {
        *len = lenRepo;
        *Array = a;
    }
    else if (optiune == 1) {
        *len = 0;
        for (int i = 0; i < lenRepo; i++)
            if (GetNume(a[i])[0] == filtru[0]) {
                b[*len] = a[i];
                ++(*len);
            }
        *Array = b;
    } else if (optiune == 2) {
        *len = 0;
        int cantitate = atoi(filtru);
        if (cantitate == 0) {
            strcat(erori, "Nu se pot afisa materii prime cu filtrul dat!\n");
            return 0;
        }
        for (int i = 0; i < lenRepo; i++)
            if (GetCantitate(a[i]) < cantitate) {
                b[*len] = a[i];
                ++(*len);
            }
        *Array = b;
    } else {
        strcat(erori, "Optiune invalida.\n");
        return 0;
    }
    if (*len == 0) {
        strcat(erori, "Nu exista materii prime cu filtrul dat.\n");
        return 0;
    }
    return 1;
}

bool Sorteaza(SERVICE_MATERII_P Service, int optiune, MATERIE_P* Array, char* erori) {
    if (erori == NULL)
        return 0;
    erori[0] = '\0';
    if (Service == NULL || Array == NULL) {
        strcat(erori, "Parametrii necorespunzatori.\n");
        return 0;
    }
    int len;
    GetAllSRV(Service, 0, "", Array, &len, erori);
    if (strlen(erori) > 0) {
        return 0;
    }
    if (optiune == 0) { //crescator dupa cantitate
        BubbleSort(*Array, ComparaCrescatorCantitate,  len);
    } else if (optiune == 1) { //crescator dupa nume
        BubbleSort(*Array, ComparaCrescatorNume,  len);
    } else if (optiune == 2) { //descrescator dupa cantitate
        BubbleSort(*Array, ComparaDescrescatorCantitate,  len);
    }else if (optiune == 3) { //descrescator dupa nume
        BubbleSort(*Array, ComparaDescrescatorNume,  len);
    } else {
        strcat(erori, "Optiune invalida!\n");
        return 0;
    }
    return 1;
}