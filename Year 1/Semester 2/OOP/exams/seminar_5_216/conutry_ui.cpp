//
// Created by Mali Imre Gergely on 04.05.2022.
//
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QDialog>
#include <QErrorMessage>
#include <vector>
#include "conutry_ui.h"

void CountryUI::setupUI(QWidget *widget) {

    widget->resize(500, 500);
    auto mainVBox = new QVBoxLayout(widget);

    auto filterLayout = new QHBoxLayout();
    this->populationFilterEdit = new QLineEdit();
    this->populationFilterButton = new QPushButton("Filter");

    filterLayout->addWidget(this->populationFilterEdit);
    filterLayout->addWidget(this->populationFilterButton);

    this->countriesListWidget = new QListWidget();
    QFont font{"Verdana", 18};
    this->countriesListWidget->setFont(font);

    auto formLayout = new QFormLayout();
    this->nameEdit = new QLineEdit();
    this->capitalEdit = new QLineEdit();
    this->populationEdit = new QLineEdit();
    formLayout->addRow("Name", this->nameEdit);
    formLayout->addRow("Capital", this->capitalEdit);
    formLayout->addRow("Population", this->populationEdit);

    auto buttonsLayout = new QHBoxLayout();
    this->addButton = new QPushButton("&Add");
    this->updateButton = new QPushButton("&Update");
    this->deleteButton = new QPushButton("&Delete");

    buttonsLayout->addWidget(this->addButton);
    buttonsLayout->addWidget(this->updateButton);
    buttonsLayout->addWidget(this->deleteButton);

    mainVBox->addLayout(filterLayout);
    mainVBox->addWidget(this->countriesListWidget);
    mainVBox->addLayout(formLayout);
    mainVBox->addLayout(buttonsLayout);

}

void CountryUI::populateList() {

    auto elems = this->service.get_all();
    this->populateList(elems);
}


void CountryUI::populateList(std::vector<Country> elements) {
    this->countriesListWidget->clear();
    for (const auto &elem: elements) {
        auto item = new QListWidgetItem(
                QString::fromStdString(
                        elem.get_name() + " "
                        + elem.get_capital() + " "
                        + std::to_string(elem.get_population()
                        )));
        this->countriesListWidget->addItem(item);
    }
}


void CountryUI::connectSignalsToSlots() {
    QObject::connect(this->addButton, &QPushButton::clicked, [&]() {
        auto name = this->nameEdit->text().toStdString();
        auto capital = this->capitalEdit->text().toStdString();
        auto population = this->populationEdit->text().toInt();
        try {
            this->service.add(name, capital, population);
        } catch (std::runtime_error &e) {
            QErrorMessage *message = new QErrorMessage();//TODO solve memory leak
            message->showMessage(e.what());

        }
        this->populateList();
    });
    QObject::connect(this->countriesListWidget, &QListWidget::itemSelectionChanged, [&]() {
        int index = this->getSelectedIndex();
        auto elements = this->service.get_all();
        if (index >= elements.size()) {
            this->nameEdit->clear();
            this->capitalEdit->clear();
            this->populationEdit->clear();
            return;
        }
        auto element = elements.at(index);
        this->nameEdit->setText(QString::fromStdString(element.get_name()));
        this->capitalEdit->setText(QString::fromStdString(element.get_capital()));
        this->populationEdit->setText(QString::fromStdString(std::to_string(element.get_population())));
    });

    QObject::connect(this->deleteButton, &QPushButton::clicked, [&]() {
        int index = this->getSelectedIndex();
        auto elements = this->service.get_all();//TODO replace with local copy for features to work after filter
        auto element = elements.at(index);
        this->service.remove(element.get_name());
        this->populateList();
    });

    QObject::connect(this->updateButton, &QPushButton::clicked, [&]() {
        auto name = this->nameEdit->text().toStdString();
        auto capital = this->capitalEdit->text().toStdString();
        auto population = this->populationEdit->text().toInt();
        try {
            this->service.update(name, capital, population);
        } catch (std::runtime_error &e) {
            QErrorMessage *message = new QErrorMessage();//TODO solve memory leak
            message->showMessage(e.what());
        }
        this->populateList();
    });

    QObject::connect(this->populationFilterButton, &QPushButton::clicked, [&]() {
        int population = this->populationFilterEdit->text().toInt();
        auto elements = this->service.find_by_population(population);
        this->populateList(elements);
    });
}

