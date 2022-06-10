//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#include "gui.h"

void Gui::init() {
    auto *mainLayout = new QVBoxLayout;

    lst = new QListWidget;
    mainLayout->addWidget(lst);

    btn_sterge = new QPushButton("Sterge");
    mainLayout->addWidget(btn_sterge);

    auto *filtr1_layout = new QHBoxLayout;
    btn_filtreaza_pret = new QPushButton("Filtreaza pret");
    pret1_edit = new QLineEdit;
    pret2_edit = new QLineEdit;
    filtr1_layout->addWidget(pret1_edit);
    filtr1_layout->addWidget(pret2_edit);
    filtr1_layout->addWidget(btn_filtreaza_pret);
    mainLayout->addLayout(filtr1_layout);

    auto *filtr2_layout = new QHBoxLayout;
    supr1_edit = new QLineEdit;
    supr2_edit = new QLineEdit;
    btn_filtreaza_suprafata = new QPushButton("Filtreaza suprafata");
    filtr2_layout->addWidget(supr1_edit);
    filtr2_layout->addWidget(supr2_edit);
    filtr2_layout->addWidget(btn_filtreaza_suprafata);
    mainLayout->addLayout(filtr2_layout);


    this->setLayout(mainLayout);
}

void Gui::load_data(std::vector <Apartament> all) {
    lst->clear();
    for(auto const& a: all) {
        lst->addItem(QString::fromStdString(a.to_string()));
    }
}

void Gui::connect() {
    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&](){
        auto index = this->lst->selectionModel()->currentIndex().row();
        auto all = this->srv.get_all();
        if (index >= all.size())
            return;
        selected_apartament = all.at(index);
    });

    QObject::connect(btn_sterge, &QPushButton::clicked, [&](){
        this->srv.remove(selected_apartament);
        load_data(this->srv.get_all());
    });

    QObject::connect(btn_filtreaza_pret, &QPushButton::clicked, [&](){
        if (!pret1_edit->text().isEmpty() && !pret2_edit->text().isEmpty()) {
            auto p1 = stod(pret1_edit->text().toStdString());
            auto p2 = stod(pret2_edit->text().toStdString());
            auto all = this->srv.filter_pret(p1, p2);
            load_data(all);
        } else {
            return;
        }
    });

    QObject::connect(btn_filtreaza_suprafata, &QPushButton::clicked, [&](){
        if (!supr1_edit->text().isEmpty() && !supr2_edit->text().isEmpty() && !pret1_edit->text().isEmpty() && !pret2_edit->text().isEmpty()){
            auto p1 = stod(pret1_edit->text().toStdString());
            auto p2 = stod(pret2_edit->text().toStdString());
            auto s1 = stoi(supr1_edit->text().toStdString());
            auto s2 = stoi(supr2_edit->text().toStdString());
            auto all = this->srv.filter_tip_suprafata(p1, p2, s1, s2);
            load_data(all);
        }
        else if (!supr1_edit->text().isEmpty() && !supr2_edit->text().isEmpty()) {
            auto s1 = stoi(supr1_edit->text().toStdString());
            auto s2 = stoi(supr2_edit->text().toStdString());
            auto all = this->srv.filter_suprafata(s1, s2);
            load_data(all);
        } else {
            return;
        }
    });

};