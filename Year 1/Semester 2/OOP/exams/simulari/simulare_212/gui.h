//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_212_GUI_H
#define SIMULARE_212_GUI_H
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <iostream>
#include <QMessageBox>
#include "service.h"

class Gui : public QWidget{
Q_OBJECT
private:
    Service& srv;
    PlacaDeBaza placa_curenta;
    Procesor procesor_curent;
    QListWidget *lst_placi;
    QListWidget *lst_procesoare;
    QLineEdit *nume_edit;
    QLineEdit *soclu_edit;
    QLineEdit *pret_edit;
    QPushButton *adauga_btn;
    QPushButton *filtreaza_btn;
    QPushButton *calculeaza_btn;


    void load_data();
    void load_data_placi(vector <PlacaDeBaza> placi);
    void init();
    void connect();
public:
    Gui(Service &srv) : srv { srv } {
        init();
        load_data();
        connect();
    };

};


#endif //SIMULARE_212_GUI_H
