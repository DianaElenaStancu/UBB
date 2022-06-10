//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef STANCU_DIANA_SIMULARE_GUI_H
#define STANCU_DIANA_SIMULARE_GUI_H
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <iostream>


#include "service.h"
using namespace std;
class Gui : public QWidget{
    Q_OBJECT
private:
    Service &srv;

    QListWidget *lst;
    QLineEdit *nume_edit;
    QLineEdit *prenume_edit;
    QLineEdit *clasa_edit;
    QLineEdit *medie_edit;
    QPushButton *sortat_medie_btn;
    QPushButton *sortat_clasa_btn;
    QPushButton *sortat_nume_btn;
    QPushButton *nesortat_btn;
    QVBoxLayout *btns_del;

    QVector<QPushButton*> buttons_f;

    /*
     * functie care elimina textul din edituri
     */
    void clear_edits();
    /*
     * functie care incarca lista in consola
     * @param: vector <Elev>
     */
    void load_data(vector <Elev> all);
    /*
     * functie care initializeaza elementele
     */
    void init();
    /*
     * functie care conecteaza signalurile de sloturi
     */
    void connect();
public:
    Gui(Service &srv) : srv {srv} {
        init();
        load_data(srv.get_all());
        connect();
    };
};


#endif //STANCU_DIANA_SIMULARE_GUI_H
