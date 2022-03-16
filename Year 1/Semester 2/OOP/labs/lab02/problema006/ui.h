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

bool AdaugaMaterieUi(UI_P Ui, char* erori);

bool StergeMaterieUi(UI_P Ui, char* erori);

bool ModificaMaterieUi(UI_P Ui, char* erori);

bool VizualizeazaUi(UI_P Ui, char* erori);

bool SorteazaUi(UI_P Ui, char* erori);

bool runUI(UI_P Ui);

#endif //PROBLEMA006_UI_H
