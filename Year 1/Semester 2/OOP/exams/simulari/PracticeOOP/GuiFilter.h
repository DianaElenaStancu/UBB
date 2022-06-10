//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef PRACTICEOOP_GUIFILTER_H
#define PRACTICEOOP_GUIFILTER_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QMessageBox>
#include "service.h"
class GuiFilter : public QWidget {
Q_OBJECT
private:
    Service &service;
    QPushButton *btnFilter;
    QListWidget *lstFilter;
    QLineEdit *filterEdit;
    QTableWidget *tblFilter;
    void init();
    void connect();

public:
    GuiFilter(Service &service) : service { service } {
        init();
        connect();
    }
};


#endif //PRACTICEOOP_GUIFILTER_H
