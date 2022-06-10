//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef SIMULARE_213_GUI_H
#define SIMULARE_213_GUI_H
#include "service.h"
#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>

class Gui : public QWidget {
    Q_OBJECT
private:
    Service &srv;
    Apartament selected_apartament;
    QListWidget *lst;
    QPushButton *btn_sterge;
    QPushButton *btn_filtreaza_suprafata;
    QPushButton *btn_filtreaza_pret;
    QLineEdit *pret1_edit;
    QLineEdit *pret2_edit;
    QLineEdit *supr1_edit;
    QLineEdit *supr2_edit;
    void init();
    void load_data(std::vector <Apartament> all);
    void connect();
public:
    Gui(Service &srv) : srv {srv} {
        init();
        load_data(srv.get_all());
        connect();
    };
};


#endif //SIMULARE_213_GUI_H
