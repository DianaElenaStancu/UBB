//
// Created by Diana-Elena Stancu on 24/05/2022.
//

#include "cosCRUDGUI.h"


void CosCRUDGUI::initComponents() {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    table = new QTableWidget(0, 4);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(table);

    slider = new QSlider;
    slider->setMinimum(0);
    slider->setMaximum(this->service.getAll().size());//!!
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksBelow);
    mainLayout->addWidget(slider);

    genereazaButton = new QPushButton("Genereaza");
    mainLayout->addWidget(genereazaButton);

    golireButton = new QPushButton("Golire");
    mainLayout->addWidget(golireButton);
}

void CosCRUDGUI::connectSignals() {
    QObject::connect(genereazaButton, &QPushButton::clicked, [this]() {
        int number = slider->value();
        this->service.genereazaLista(number);
        cos.notify();
    });
    QObject::connect(golireButton, &QPushButton::clicked, [this]() {
        this->service.golesteLista();
        cos.clear();
        cos.notify();
    });
}

void CosCRUDGUI::populateTable(QTableWidget* table, const vector<Activitate>& all) {
    table->clear();
    int nr = 0;
    table->setRowCount(all.size());
    for (const auto& a : all) {
        //table->insertRow(nr);
        table->setItem(nr, 0, new QTableWidgetItem(QString::fromStdString(a.getTitlu())));
        table->setItem(nr, 1, new QTableWidgetItem(QString::fromStdString(a.getDescriere())));
        table->setItem(nr, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
        table->setItem(nr, 3, new QTableWidgetItem(QString::number(a.getDurata())));
        ++nr;
    }
}

void CosCRUDGUI::update() {
    this->populateTable(table, this->cos.getAll());
}