//
// Created by Diana-Elena Stancu on 15/03/2022.
//

#include "ui.h"

bool CreeazaUI(UI_P* Ui, SERVICE_MATERII_P Service) {
    if (Ui == NULL || Service == NULL) return 0;
    UI_P console = (UI_P)malloc(sizeof(UI));
    console -> Service = Service;
    *Ui = console;
    return 1;
}

bool DistrugeUI(UI_P* Ui) {
    if (Ui == NULL) return 0;
    SERVICE_MATERII_P service = (*Ui)->Service;
    if (DistrugeService(&service) == 0) return 0;
    free(*Ui);
    return 1;
}

int CitesteCmd() {
    printf("\n************\nComezi disponibile:\n0 - Exit\n1 - Adauga materie prima\n2 - Sterge materie prima\n3 - Modifica materie prima\n4 - Vizualizarea materii prime\n5 - Filtreaza materii prime\n************\nComanda ta este -> ");
    int cmd;
    scanf ("%d", &cmd);
    return cmd;
}

bool AdaugaMaterieUi(UI_P Ui, char* erori) {
    erori[0] = '\0';
    char *nume, *producator;
    int cantitate;
    bool success;

    nume = (char*) malloc(sizeof(char)*INPUT_SIZE);
    producator = (char*) malloc(sizeof(char)*INPUT_SIZE);
    printf("Adauga materie in formatul: nume prenume cantitate\n-> ");
    scanf("%s %s %d", nume, producator, &cantitate);
    success = AdaugaMaterieSRV(Ui->Service, nume, producator, cantitate, erori);
    free(nume);
    free(producator);
    if (!success)
        strcat(erori, "Adaugare esuata!\n");
    return success;
}

bool StergeMaterieUi(UI_P Ui, char* erori) {
    erori[0] = '\0';
    char *nume;
    bool success;

    nume = (char*) malloc(sizeof(char)*INPUT_SIZE);
    printf("Sterge materia cu numele\n -> ");
    scanf("%s", nume);
    success = StergeMaterieSRV(Ui->Service, nume, erori);
    free(nume);
    if (!success)
        strcat(erori, "Stergere esuata!\n");
    return success;
}

bool ModificaMaterieUi(UI_P Ui, char* erori) {
    erori[0] = '\0';
    char *nume, *producator;
    int cantitate;
    bool success;

    nume = (char*) malloc(sizeof(char)*INPUT_SIZE);
    producator = (char*) malloc(sizeof(char)*INPUT_SIZE);
    printf("Materia pe care vrei sa o modifici in formatul: nume prenume cantitate\n-> ");
    scanf("%s %s %d", nume, producator, &cantitate);
    success = ModificaMaterieSRV(Ui->Service, nume, producator, cantitate, erori);
    free(nume);
    free(producator);
    if (!success)
        strcat(erori, "Modificare esuata!\n");
    return success;
}

bool VizualizeazaUi(UI_P Ui, char* erori) {
    erori[0] = '\0';
    MATERIE_P Array;
    printf("0.Vizualizeaza tot\n1.Vizualizeaza dupa nume\n2.Vizualizeaza dupa cantitate.\nComanda ta este -> ");
    int cmd;
    char filtru[10] = "";
    scanf ("%d", &cmd);
    int len;
    if (cmd == 1) {
        printf("Initiala nume materie: ");
        scanf("%s", filtru);
    }
    else if (cmd == 2) {
        printf("Cantitate dorita: ");
        scanf("%s", filtru);
    }

    bool success = GetAllSRV(Ui->Service, cmd, filtru, &Array, &len, erori);
    if (!success) {
        strcat(erori, "Vizualizarea a esuat!\n");
        return 0;
    }

    for (int i = 0; i < len; i++)
        PrintMaterie(Array[i]);
    return 1;
}

bool SorteazaUi(UI_P Ui, char* erori) {
    erori[0] = '\0';
    MATERIE_P Array;
    printf("Sorteaza dupa:\n0.Crescator dupa cantitate\n1.Crescator dupa nume\n2.Descrescator dupa cantitate\n3.Descrescator dupa nume\nOptiunea ta este -> ");
    int cmd;
    scanf ("%d", &cmd);
    int len = GetLungimeREPO(Ui->Service->Repository);
    bool success = Sorteaza(Ui->Service, cmd, &Array, erori);
    if (!success) {
        strcat(erori, "Sortarea a esuat!\n");
        return 0;
    }

    for (int i = 0; i < len; i++)
        PrintMaterie(Array[i]);
    return 1;
}

bool runUI(UI_P Ui) {
    if (Ui == NULL) return 0;
    char *erori = (char*) malloc (100 * sizeof(char));
    bool exit = 0;
    while(!exit) {
        int cmd = CitesteCmd();
        bool success = 1;
        if (cmd == 0)
            exit = 1;
        else if (cmd == 1)
            success = AdaugaMaterieUi(Ui, erori);
        else if (cmd == 2)
            success = StergeMaterieUi(Ui, erori);
        else if (cmd == 3)
            success = ModificaMaterieUi(Ui, erori);
        else if (cmd == 4)
            success = VizualizeazaUi(Ui, erori);
        else if (cmd == 5)
            success = SorteazaUi(Ui, erori);
        else
            printf("Comanda invalida!\n");

        if (!success) {
            printf("%s", erori);
        }
    }
    printf("Bye bye!");
}