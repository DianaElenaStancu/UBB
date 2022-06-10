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
#include <time.h>
class Gui : public QWidget{
    Q_OBJECT
private:
    Service &srv;
    QListWidget *lst;
    QSlider *sld;
    QLineEdit *nume_edit;
    QLineEdit *tara_edit;
    QPushButton *adauga_btn;
    QPushButton *generate_btn;
    QVector <QRadioButton*> btn_lst;
    QHBoxLayout *btn_layout;


    void init();
    void load_btns();
    void load_data(vector <Jucator> all);
    void connect();
public:
    Gui(Service &srv) : srv { srv } {
        init();
        load_btns();
        load_data(srv.get_all());
        connect();
    };
};


#endif //SIMULARE_216_V1_GUI_H
