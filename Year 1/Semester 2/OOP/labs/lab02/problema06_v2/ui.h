//
// Created by Diana-Elena Stancu on 15/03/2022.
//

#ifndef PROBLEMA006_UI_H
#define PROBLEMA006_UI_H

#include "service.h"
#include <stdbool.h>
#define INPUT_SIZE 20

typedef struct UI {
    SERVICE_MATERII_P Service;
} UI, *UI_P;

/*
 * functia creeaza functionalitatea de UI
 *
 * @parametrii: Ui - pointer spre un pointer spre Ui
 *              Service - pointer la service
 *
 * @return: 1 - daca ui-ul a fost creat cu succes
 *          0 - altfel
 */
bool CreeazaUI(UI_P* Ui, SERVICE_MATERII_P Service);

/*
 * functia distruge functionalitatea de UI
 *
 * @parametrii: Ui - pointer spre un pointer spre Ui
 *
 * @return: 1 - daca ui-ul a fost distrus cu succes
 *          0 - altfel
 */
bool DistrugeUI(UI_P* Ui);

/*
 * functia afiseaza meniul si citeste de la tastatura comanda
 *
 * @parametrii: -
 *
 * @return: comanda (integer)
 */
int CitesteCmd();

/*
 * functia citeste parmetrii materiei si adauga
 *
 * @parametrii: Ui - interfata
 *              erori - sir de erori
 *
 * @return: 1 - daca adaugarea a avut succes
 *          0 - altfel
 */
bool AdaugaMaterieUi(UI_P Ui, char* erori);

/*
 * functia citeste numele materiei si sterge materia cu numele dat
 *
 * @parametrii: Ui - interfata
 *              erori - sir de erori
 *
 * @return: 1 - daca stergerea a avut succes
 *          0 - altfel
 */
bool StergeMaterieUi(UI_P Ui, char* erori);

/*
 * functia citeste parmetrii materiei si modifica materia cu numele dat
 *
 * @parametrii: Ui - interfata
 *              erori - sir de erori
 *
 * @return: 1 - daca modificarea a avut succes
 *          0 - altfel
 */
bool ModificaMaterieUi(UI_P Ui, char* erori);

/*
 * functia citeste optiunea/filtrul pentru afisare
 *
 * @parametrii: Ui - interfata
 *              erori - sir de erori
 *
 * @return: 1 - daca vizualizarea a avut succes
 *          0 - altfel
 */
bool VizualizeazaUi(UI_P Ui, char* erori);

/*
 * functia citeste optiunea pentru sortare
 *
 * @parametrii: Ui - interfata
 *              erori - sir de erori
 *
 * @return: 1 - daca sortarea a avut succes
 *          0 - altfel
 */
bool SorteazaUi(UI_P Ui, char* erori);

/*
 * functia care ruleaza aplicatia
 *
 * @parametrii: Ui - interfata
 *
 * @return: -
 */
void runUI(UI_P Ui);

#endif //PROBLEMA006_UI_H
