//
// Created by Mali Imre Gergely on 04.05.2022.
//

#ifndef SEMINAR_EXAMPLE_CONUTRY_UI_H
#define SEMINAR_EXAMPLE_CONUTRY_UI_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "service.h"
#include <iostream>

class CountryUI : public QWidget {
Q_OBJECT
private:
    Service &service;
    QListWidget *countriesListWidget;
    QLineEdit *nameEdit;
    QLineEdit *capitalEdit;
    QLineEdit *populationEdit;

    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;

    QLineEdit* populationFilterEdit;
    QPushButton* populationFilterButton;

    void setupUI(QWidget *widget);

public:
    CountryUI(Service &s) : service{s} {
        this->setupUI(this);
        this->connectSignalsToSlots();
        this->populateList();
    }

    void populateList(std::vector<Country> elements);
    void populateList();

    int getSelectedIndex() {
        auto currentIndex = this->countriesListWidget->selectionModel()->currentIndex();
        return currentIndex.row();
    }

    void connectSignalsToSlots() ;

};


#endif //SEMINAR_EXAMPLE_CONUTRY_UI_H
