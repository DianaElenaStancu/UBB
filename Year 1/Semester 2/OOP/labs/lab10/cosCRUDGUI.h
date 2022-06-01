//
// Created by Diana-Elena Stancu on 24/05/2022.
//

#ifndef LAB10_COSCRUDGUI_H
#define LAB10_COSCRUDGUI_H

#include "service.h"
#include "Observer.h"
#include "cosActivitati.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qslider.h>
#include <qlayout>
#include <vector>

using std::vector;

class CosCRUDGUI : public QWidget, public Observer {
private:
    CosActivitati& cos;
    Service& service;

    QTableWidget* table;
    QSlider* slider;
    QPushButton* genereazaButton;
    QPushButton* golireButton;

    void initComponents();
    void connectSignals();

    void populateTable(QTableWidget* table, const vector<Activitate>& all);

public:
    CosCRUDGUI(CosActivitati& cos, Service& service): cos{ cos }, service{ service } {
        this->cos.addObserver(this);

        this->initComponents();
        this->connectSignals();
        this->update();
    };

    void update() override;

    ~CosCRUDGUI() {
        this->cos.removeObserver(this);
    }
};


#endif //LAB10_COSCRUDGUI_H
