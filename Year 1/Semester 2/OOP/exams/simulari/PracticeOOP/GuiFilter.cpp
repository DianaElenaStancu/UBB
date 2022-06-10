//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#include "GuiFilter.h"

void GuiFilter::init() {
    auto *mainLayout = new QVBoxLayout;
    lstFilter = new QListWidget;
    mainLayout->addWidget(lstFilter);

    tblFilter = new QTableWidget(0, 4);
    tblFilter->setHorizontalHeaderItem(0, new QTableWidgetItem("Nr"));
    tblFilter->setHorizontalHeaderItem(1, new QTableWidgetItem("Producator"));
    tblFilter->setHorizontalHeaderItem(2, new QTableWidgetItem("Tip"));
    tblFilter->setHorizontalHeaderItem(3, new QTableWidgetItem("Model"));

    mainLayout->addWidget(tblFilter);

    auto *filterLayout = new QHBoxLayout;
    filterEdit = new QLineEdit;
    btnFilter = new QPushButton("Cauta");
    filterLayout->addWidget(filterEdit);
    filterLayout->addWidget(btnFilter);
    mainLayout->addLayout(filterLayout);

    this->setLayout(mainLayout);
}


void GuiFilter::connect() {
    QObject::connect(btnFilter, &QPushButton::clicked, [&](){
        auto filtru = filterEdit->text().toStdString();
        auto masini_filtrate = service.filter(filtru);

        //lista
        lstFilter->clear();
        for (auto const& m: masini_filtrate) {
            lstFilter->addItem(QString::fromStdString(m.toString()));
        }

        //tabel
        tblFilter->clear();
        int nbItems = 0;
        tblFilter->setRowCount(masini_filtrate.size());
        for (auto const& m: masini_filtrate) {
            tblFilter->setVerticalHeaderItem(nbItems, new QTableWidgetItem(QString::number(nbItems)));
            tblFilter->setItem(nbItems, 0, new QTableWidgetItem(QString::fromStdString(m.GetNrInmatriculare())));
            tblFilter->setItem(nbItems, 1, new QTableWidgetItem(QString::fromStdString(m.GetProducator())));
            tblFilter->setItem(nbItems, 2, new QTableWidgetItem(QString::fromStdString(m.GetTip())));
            tblFilter->setItem(nbItems, 3, new QTableWidgetItem(QString::fromStdString(m.GetModel())));

            nbItems++;
        }

    });

    QObject::connect(tblFilter, &QTableWidget::itemSelectionChanged, [&]() {
        auto index = tblFilter->selectionModel()->currentIndex().row();
        auto masini = service.getAll();
        if (index >= masini.size())
            return;
        auto masina = masini.at(index);
        QMessageBox::information(nullptr, "Masina detalii", QString::fromStdString(masina.toString()));
    });
}