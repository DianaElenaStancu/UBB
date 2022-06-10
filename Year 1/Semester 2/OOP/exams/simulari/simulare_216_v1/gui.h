//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_216_V1_GUI_H
#define SIMULARE_216_V1_GUI_H
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QRadioButton>
#include <QSlider>
#include <QLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "service.h"
class Gui : public QWidget{
    Q_OBJECT
private:
    Service &srv;
    QListWidget *lst;
    QLineEdit *nume_edit;
    QLineEdit *puncte_edit;
    QRadioButton *finala_btn;
    QRadioButton *semifinala_btn;
    QRadioButton *sferturi_btn;
    QPushButton *recalc_btn;
    QPushButton *elimina_btn;

    QSlider *sld;

    void init();
    void load_data();
    void connect();
public:
    Gui(Service &srv) : srv { srv } {
        init();
        load_data();
        connect();
    };
};


#endif //SIMULARE_216_V1_GUI_H
