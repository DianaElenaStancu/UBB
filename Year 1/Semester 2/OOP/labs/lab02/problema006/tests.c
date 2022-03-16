//
// Created by Diana-Elena Stancu on 14/03/2022.
//

#include "tests.h"



void runTests(){
    testDomain();
    testValidator();
    testRepo();
    testService();
    testUtils();
//testAdauga();
}

void testDomain() {
    //creare materie
    MATERIE_P Materie, MaterieDif;
    assert(CreeazaMaterie(&Materie, "zahar", "pambac", 200));
    assert(CreeazaMaterie(&MaterieDif, "lapte", "pambac", 200));
    assert(!CreeazaMaterie(NULL, "zahar", "pambac", 200));

    //get si set
    SetNume(Materie, "faina");
    assert(strcmp(GetNume(*Materie), "faina") == 0);
    SetProducator(Materie, "zuzu");
    assert(strcmp(GetProducator(*Materie), "zuzu") == 0);
    SetCantitate(Materie, 1000);
    assert(GetCantitate(*Materie) == 1000);

    //compara materii
    assert(MateriiEgale(*Materie, *Materie));
    assert(MateriiEgale(*Materie, *MaterieDif) == 0);
    assert(ComparaCrescatorNume(*Materie, *MaterieDif) == 1);
    assert(ComparaDescrescatorNume(*Materie, *MaterieDif) == 0);
    SetNume(Materie, "vafe");
    assert(ComparaCrescatorNume(*Materie, *MaterieDif) == 0);
    assert(ComparaDescrescatorNume(*Materie, *MaterieDif) == 1);
    SetNume(Materie, "lapte");
    assert(ComparaCrescatorNume(*Materie, *MaterieDif) == 0);
    assert(ComparaCrescatorCantitate(*Materie, *MaterieDif) == 0);
    assert(ComparaDescrescatorNume(*Materie, *MaterieDif) == 1);
    assert(ComparaDescrescatorCantitate(*Materie, *MaterieDif) == 1);
    SetCantitate(MaterieDif, 10000);
    assert(ComparaCrescatorCantitate(*Materie, *MaterieDif) == 1);
    assert(ComparaDescrescatorCantitate(*Materie, *MaterieDif) == 0);
    SetCantitate(MaterieDif, 1000);
    SetNume(Materie, "albalact");
    assert(ComparaCrescatorCantitate(*Materie, *MaterieDif) == 1);
    assert(ComparaDescrescatorCantitate(*Materie, *MaterieDif) == 0);

    //distrugere materie
    assert(DistrugeMaterie(&Materie));
    assert(DistrugeMaterie(&MaterieDif));
    assert(Materie == NULL);
    assert(MaterieDif == NULL);
}

void testValidator() {
    MATERIE_P Materie, MaterieInv;
    char* erori = (char*)malloc(sizeof(char) * 100);
    erori[0] = '\0';
    assert(CreeazaMaterie(&Materie, "zahar", "pambac", 200));
    assert(ValideazaMaterie(*Materie, erori));
    assert(strlen(erori) == 0);
    assert(CreeazaMaterie(&MaterieInv, "", "", 0));
    assert(ValideazaMaterie(*MaterieInv, erori) == 0);
    assert(strcmp(erori, "Nume invalid\nProducator invalid\nCantitate invalida\n") == 0);
    DistrugeMaterie(&Materie);
    DistrugeMaterie(&MaterieInv);
    free(erori);
}

void testRepo() {
    //creare repo
    REPOSITORY_MATERII_P Repo = NULL;
    assert(CreeazaRepository(&Repo));
    assert(CreeazaRepository(NULL) == 0);
    assert(GetLungimeREPO(Repo) == 0);
    assert(Repo->Capacitate == 2);

    //inserare materie
    MATERIE_P m1, m2, m3, m4, m5;
    CreeazaMaterie(&m1, "lapte", "milka", 200);
    CreeazaMaterie(&m2, "faina", "pambac", 700);
    CreeazaMaterie(&m3, "oua", "local", 1000);
    CreeazaMaterie(&m4, "lapte", "milka", 3000);
    CreeazaMaterie(&m5, "zahar", "zuzu", 10000);

    assert(AdaugaMaterieREPO(Repo, m1));
    assert(GetLungimeREPO(Repo) == 1);
    assert(AdaugaMaterieREPO(Repo, m3));
    assert(GetLungimeREPO(Repo) == 2);
    assert(AdaugaMaterieREPO(Repo, m2));
    assert(GetLungimeREPO(Repo) == 3);
    assert(Repo->Capacitate == 4);
    assert(AdaugaMaterieREPO(Repo, m4));
    assert(GetLungimeREPO(Repo) == 3);
    assert(Repo->Capacitate == 4);

    //getall materie
    MATERIE_P m = (MATERIE_P) malloc(sizeof(MATERIE));
    assert(GetAll(NULL, &m) == 0);
    assert(GetAll(Repo, NULL) == 0);
    assert(GetAll(Repo, &m) == 1);

    assert(CautaMaterieREPO(Repo, *m1) != -1);
    assert(CautaMaterieREPO(Repo, *m3) != -1);

    //modifica materii
    assert(ModificaMaterieREPO(NULL, m5) == 0);
    assert(ModificaMaterieREPO(Repo, NULL) == 0);
    assert(ModificaMaterieREPO(Repo, m4) == 1);
    assert(ModificaMaterieREPO(Repo, m5) == 0);


    //sterge materii
    assert(StergeMaterieREPO(Repo, *m5) == 0);
    assert(StergeMaterieREPO(Repo, *m1) == 1);
    //cauta materii
    assert(CautaMaterieREPO(Repo, *m1) == -1);
    assert(GetLungimeREPO(Repo) == 2);
    assert(StergeMaterieREPO(Repo, *m3) == 1);
    assert(GetLungimeREPO(Repo) == 1);
    assert(Repo->Capacitate == 2);

    //distruge repo
    assert(DistrugeRepository(&Repo));
    assert(DistrugeRepository(NULL) == 0);
    assert(Repo == NULL);
}

void testService(){
    MATERIE_P m1, m2, m3;
    CreeazaMaterie(&m1, "lapte", "zuzu", 200);
    CreeazaMaterie(&m2, "faina", "pambac", 200);
    CreeazaMaterie(&m3, "lapte", "milka", 1000);
    //creeaza
    SERVICE_MATERII_P service;
    Validator validator = ValideazaMaterie;
    REPOSITORY_MATERII_P repository1, repository2 = NULL;

    CreeazaRepository(&repository1);
    CreeazaRepository(&repository2);

    assert(CreeazaService(NULL, NULL, NULL) == 0);
    assert(CreeazaService(NULL, repository1, NULL) == 0);
    assert(CreeazaService(&service, repository2, validator));

    //GetAll materii
    //adauga materie
    MATERIE_P Array;
    MATERIE_P sortedArray;
    int len;
    char* erori = (char*)malloc(100*sizeof(char));
    assert(GetAllSRV(service,  0, "",&Array, &len, erori) == 0);
    assert(strcmp(erori, "Nu exista materii prime in cofetarie!\n") == 0);
    assert(AdaugaMaterieSRV(service, "lapte", "zuzu", 200, erori));
    assert(strlen(erori) == 0);
    assert(GetLungimeREPO(service->Repository) == 1);
    assert(AdaugaMaterieSRV(service, NULL, NULL, 0, erori) == 0);
    assert(strcmp(erori, "parametrii invalizi!\n") == 0);
    assert(AdaugaMaterieSRV(service,"lapte", "zuzu", -10, erori) == 0);
    assert(strcmp(erori, "Cantitate invalida\n") == 0);

    //GetAll materii
    assert(GetAllSRV(service, 0, "", &Array, &len, NULL) == 0);
    assert(GetAllSRV(NULL, 0, "", NULL, &len, erori) == 0);
    assert(strlen(erori) > 0);
    assert(strcmp(erori, "parametrii invalizi!\n") == 0);
    assert(GetAllSRV(service, 0, "", &Array, &len, erori));
    assert(len == 1);
    assert(strlen(erori) == 0);
    assert(strcmp(GetNume(Array[0]), "lapte") == 0);
    assert(strcmp(GetProducator(Array[0]), "zuzu") == 0);
    assert(GetCantitate(Array[0]) == 200);
    assert(GetAllSRV(service, 20, "", &Array, &len, erori) == 0);
    assert(strcmp(erori, "Optiune invalida.\n") == 0);
    assert(GetAllSRV(service, 1, "c", &Array, &len, erori) == 0);
    assert(strcmp(erori, "Nu exista materii prime cu filtrul dat.\n") == 0);
    assert(GetAllSRV(service, 1, "lapte", &Array, &len, erori));
    assert(strlen(erori) == 0);
    assert(strcmp(GetNume(Array[0]), "lapte") == 0);
    assert(strcmp(GetProducator(Array[0]), "zuzu") == 0);
    assert(GetCantitate(Array[0]) == 200);
    assert(GetAllSRV(service, 2, "300", &Array, &len, erori));
    assert(strlen(erori) == 0);
    assert(strcmp(GetNume(Array[0]), "lapte") == 0);
    assert(strcmp(GetProducator(Array[0]), "zuzu") == 0);
    assert(GetCantitate(Array[0]) == 200);
    assert(GetAllSRV(service, 2, "sahd", &Array, &len, erori) == 0);
    assert(strcmp(erori, "Nu se pot afisa materii prime cu filtrul dat!\n") == 0);
    assert(GetAllSRV(service, 2, "10", &Array, &len, erori) == 0);
    assert(strcmp(erori, "Nu exista materii prime cu filtrul dat.\n") == 0);

    //modifica materii
    assert(ModificaMaterieSRV(service, "lapte", "zuzu", 200, NULL) == 0);
    assert(ModificaMaterieSRV(NULL, "lapte", "zuzu", 200, erori) == 0);
    assert(strcmp(erori, "parametrii invalizi!\n") == 0);
    assert(ModificaMaterieSRV(service, "lapte", "milka", 1000, erori));
    assert(strlen(erori) == 0);
    assert(GetAllSRV(service,  0, "",&Array, &len, erori));
    assert(len == 1);
    assert(strlen(erori) == 0);
    assert(strcmp(GetNume(Array[0]), "lapte") == 0);
    assert(strcmp(GetProducator(Array[0]), "milka") == 0);
    assert(GetCantitate(Array[0]) == 1000);
    assert(ModificaMaterieSRV(service, "budinca", "milka", 1000, erori) == 0);
    assert(strcmp(erori,"Materia nu a putut fi modificata.\n") == 0);
    assert(ModificaMaterieSRV(service, "lapte", "milka", -38, erori) == 0);
    assert(strcmp(erori,"Cantitate invalida\nModificarea nu poate avea loc, parametrii invalizi!\n") == 0);



    //sorteaza
    assert(AdaugaMaterieSRV(service, "faina", "pambac", 200, erori));
    assert(GetAllSRV(service,  0, "",&Array, &len, erori));
    assert(Sorteaza(NULL, 0, NULL, NULL) == 0);
    assert(Sorteaza(NULL, 0, NULL, erori) == 0);
    assert(strcmp(erori, "Parametrii necorespunzatori.\n") == 0);
    assert(Sorteaza(service, -20, &Array, erori) == 0);
    assert(strcmp(erori, "Optiune invalida!\n") == 0);
    assert(Sorteaza(service, 0, &sortedArray, erori));
    assert(MateriiEgale(*m2,sortedArray[0]));//faina 200
    assert(MateriiEgale(*m3,sortedArray[1]));//lapte 1000
    assert(Sorteaza(service, 1, &sortedArray, erori));
    assert(MateriiEgale(*m2,sortedArray[0]));
    assert(MateriiEgale(*m3,sortedArray[1]));
    assert(Sorteaza(service, 2, &sortedArray, erori));
    assert(MateriiEgale(*m2,sortedArray[1]));//faina 200
    assert(MateriiEgale(*m3,sortedArray[0]));//lapte 1000
    assert(Sorteaza(service, 3, &sortedArray, erori));
    assert(MateriiEgale(*m2,sortedArray[1]));
    assert(MateriiEgale(*m3,sortedArray[0]));

    //sterge materie
    assert(StergeMaterieSRV(NULL, NULL, NULL) == 0);
    assert(StergeMaterieSRV(NULL, NULL, erori) == 0);
    assert(strcmp("Parametrii invalizi!\n", erori) == 0);
    assert(StergeMaterieSRV(service, "lapte", erori));
    assert(StergeMaterieSRV(service, "faina", erori));
    assert(GetLungimeREPO(service->Repository) == 0);
    assert(StergeMaterieSRV(service, "lapte", erori) == 0);
    assert(strcmp("Materia nu exista in repo!\n", erori) == 0);
    assert(Sorteaza(service, 3, &sortedArray, erori) == 0);


    //distruge
    assert(DistrugeService(NULL) == 0);
    assert(DistrugeService(&service));
    assert(service == NULL);
}

void testUtils() {
    MATERIE_P Array = (MATERIE_P)malloc(10*sizeof(MATERIE));
    MATERIE_P m1, m2;
    CreeazaMaterie(&m1, "lapte", "zuzu", 200);
    CreeazaMaterie(&m2, "faina", "zuzu", 100);

    Array[0] = *m1;
    Array[1] = *m2;

    BubbleSort(Array, ComparaCrescatorNume, 2);
    assert(MateriiEgale(Array[1], *m1));
    assert(MateriiEgale(Array[0], *m2));

    BubbleSort(Array, ComparaDescrescatorNume, 2);
    assert(MateriiEgale(Array[0], *m1));
    assert(MateriiEgale(Array[1], *m2));

    BubbleSort(Array, ComparaDescrescatorCantitate, 2);
    assert(MateriiEgale(Array[0], *m1));
    assert(MateriiEgale(Array[1], *m2));

    BubbleSort(Array, ComparaCrescatorCantitate, 2);
    assert(MateriiEgale(Array[1], *m1));
    assert(MateriiEgale(Array[0], *m2));
}

void testAdauga() {
    MATERIE_P m1, m2, m3;
    CreeazaMaterie(&m1, "lapte", "zuzu", 200);
    CreeazaMaterie(&m2, "faina", "pambac", 200);
    CreeazaMaterie(&m3, "lapte", "zuzu", 200);
    //creeaza
    SERVICE_MATERII_P service;
    Validator validator = ValideazaMaterie;
    REPOSITORY_MATERII_P repository1;

    CreeazaRepository(&repository1);
    char* erori = (char*)malloc(sizeof(char)*100);
    int len;
    MATERIE_P Array;
    assert(CreeazaService(&service, repository1, validator));
    assert(AdaugaMaterieSRV(service, "lapte", "zuzu", 200, erori));
    assert(AdaugaMaterieSRV(service, "faina", "pambac", 200, erori));
    assert(GetAllSRV(service, 0, "", &Array, &len, erori));

}