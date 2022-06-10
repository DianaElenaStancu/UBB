//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_217_GUI_H
#define SIMULARE_217_GUI_H
#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include "service.h"
#include <iostream>

class Gui : public QWidget {
Q_OBJECT
private:
    Service &srv;
    int state = 0;

    QListWidget *lst;
    QLineEdit *model_edit;
    QLineEdit *an_edit;
    QPushButton *sort_model;
    QPushButton *sort_an;
    QPushButton *sort_none;

    void init();
    void load_data(vector <Device> all) const;
    void connect();
public:
    Gui(Service &srv) : srv { srv} {
        init();
        load_data(this->srv.get_all());
        connect();
    };
};


#endif //SIMULARE_217_GUI_H
