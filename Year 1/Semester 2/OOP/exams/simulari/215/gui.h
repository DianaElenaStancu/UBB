//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef INC_215_GUI_H
#define INC_215_GUI_H
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include "service.h"

class Gui : public QWidget {
Q_OBJECT
private:
    Service& srv;

    QTableWidget *tbl;
    QLabel *age_lbl;

    void load_data(vector <Joc> all);
    void init();
    void connect();
public:
    Gui(Service &srv) : srv { srv } {
        init();
        load_data(srv.get_all());
        connect();
    };
};


#endif //INC_215_GUI_H
