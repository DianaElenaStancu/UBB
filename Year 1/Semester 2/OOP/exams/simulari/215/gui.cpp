//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "gui.h"

void Gui::load_data(vector <Joc> all) {
    tbl->clear();
    tbl->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Titlu")));
    tbl->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Pret")));
    int nr = 0;
    tbl->setRowCount(all.size());
    for (const auto& j: all) {
        auto *nr_wid = new QTableWidgetItem(QString::number(nr));
        nr_wid->setBackground(Qt::red);
        tbl->setVerticalHeaderItem(nr, nr_wid);
        tbl->setItem(nr, 0,new QTableWidgetItem(QString::fromStdString(j.get_titlu())));
        tbl->setItem(nr, 1,new QTableWidgetItem(QString::number(j.get_pret())));
        ++nr;
    }
}

void Gui::init() {
    auto *main_layout = new QVBoxLayout;

    tbl = new QTableWidget(0, 2);
    main_layout->addWidget(tbl);

    age_lbl = new QLabel("varsta minima acceptata este ");
    main_layout->addWidget(age_lbl);

    this->setLayout(main_layout);
}

void Gui::connect() {
    QObject::connect(tbl, &QTableWidget::itemSelectionChanged, [&](){
        auto index = tbl->selectionModel()->currentIndex().row();
        auto all = this->srv.get_all();
        if (index >= all.size())
            return;
        auto j = all.at(index);
        age_lbl->setText(QString::fromStdString("varsta minima acceptata este " + std::to_string(j.get_rating())));
    });
}