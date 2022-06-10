//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#ifndef PRACTICEOOP_GUI_H
#define PRACTICEOOP_GUI_H
#include "service.h"
#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QFormLayout>
#include <qmessagebox.h>
#define Connect QObject::connect
#define MsgBox(msg) QMessageBox::information(this, "Info", msg);

class Gui : public QWidget {
Q_OBJECT
private:
    Service &service;
    QListWidget *mainList;
    QPushButton *btnAdd;
    QPushButton *btnDel;
    QPushButton *btnModify;
    QPushButton *btnClear;
    QPushButton *btnUndo;
    QLineEdit *nrLineEdit;
    QLineEdit *producatorLineEdit;
    QLineEdit *tipLineEdit;
    QLineEdit *modelLineEdit;
    QVBoxLayout *mainLayout;
    void init();
    void loadData();
    void connectSignalsToSlots();
public:
    Gui(Service &service) : service {service} {
        init();
        loadData();
        connectSignalsToSlots();
    };
};


#endif //PRACTICEOOP_GUI_H
