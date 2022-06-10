//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#ifndef EXAMEN_STANCU_UI_H
#define EXAMEN_STANCU_UI_H
#include "service.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QTableWidget>
#include <QMessageBox>

class Ui : public QWidget, public Observer{
private:
    Service &srv;

    QVBoxLayout *main;
    QTableWidget *tabel;
    QLineEdit *id;
    QLineEdit *descriere;
    QLineEdit *stare;
    QLineEdit *progr;
    QLineEdit *cauta;
    QPushButton *add;
    QPushButton *search;

    /*
     * initializeaza fereastra
     */
    void init();
    /*
     * adauga lista in fereastra
     */
    void load(vector <Task> t);
    /*
     * conecteaza lista in fereastra
     */
    void connect();
public:
    Ui(Service &srv) : srv {srv} {
        srv.addObserver(this);
        init();
        load(srv.getAll());
        connect();
    };
    void update() override{
        load(srv.getAll());
    }
    ~Ui() {
        srv.removeObserver(this);
    }
};


#endif //EXAMEN_STANCU_UI_H
