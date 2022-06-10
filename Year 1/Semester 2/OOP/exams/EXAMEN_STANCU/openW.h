//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#ifndef EXAMEN_STANCU_OPENW_H
#define EXAMEN_STANCU_OPENW_H


#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include "service.h"
#include "observer.h"

class openW : public QWidget, public Observer{
Q_OBJECT
private:
    Service &srv;

    QVBoxLayout *main;
    QPushButton *open;
    QPushButton *closed;
    QPushButton *inprogress;
    QTableWidget *lista;


    void init();
    void load();
    void connect();
public:
    openW(Service &srv) : srv { srv } {
        srv.addObserver(this);
        init();
        load();
        connect();
    }

    void update() override{
        load();
    }

    ~openW() {
        this->srv.removeObserver(this);
    }
};


#endif //EXAMEN_STANCU_OPENW_H
