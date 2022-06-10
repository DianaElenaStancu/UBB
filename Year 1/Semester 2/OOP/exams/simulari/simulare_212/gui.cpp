//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "gui.h"


void Gui::init() {
    auto *main_layout = new QVBoxLayout;

    auto *liste = new QHBoxLayout;
    lst_placi = new QListWidget;
    lst_procesoare = new QListWidget;
    liste->addWidget(lst_procesoare);
    liste->addWidget(lst_placi);
    main_layout->addLayout(liste);


    auto *form = new QFormLayout;
    nume_edit = new QLineEdit;
    soclu_edit = new QLineEdit;
    pret_edit = new QLineEdit;
    form->addRow("Nume", nume_edit);
    form->addRow("Soclu", soclu_edit);
    form->addRow("Pret", pret_edit);
    main_layout->addLayout(form);

    auto *btns = new QHBoxLayout;
    adauga_btn = new QPushButton("Adauga");
    filtreaza_btn = new QPushButton("Filtreaza");
    calculeaza_btn = new QPushButton("Calculeaza");
    btns->addWidget(adauga_btn);
    btns->addWidget(filtreaza_btn);
    btns->addWidget(calculeaza_btn);
    main_layout->addLayout(btns);

    this->setLayout(main_layout);
}

void Gui::load_data(){
    lst_placi->clear();
    lst_procesoare->clear();
    auto placi = this->srv.get_placi();
    auto proc = this->srv.get_proc();

    for (auto const& p: proc) {
        lst_procesoare->addItem(QString::fromStdString(p.to_string()));
    }

    for (auto const& p: placi) {
        lst_placi->addItem(QString::fromStdString(p.to_string()));
    }
}
void Gui::load_data_placi(vector <PlacaDeBaza> placi) {
    lst_placi->clear();
    for (auto const& p: placi) {
        lst_placi->addItem(QString::fromStdString(p.to_string()));
    }
}
void Gui::connect() {
    QObject::connect(adauga_btn, &QPushButton::clicked, [&](){
        if(nume_edit->text().isEmpty() || soclu_edit->text().isEmpty() || pret_edit->text().isEmpty())
            return;
        auto nume = nume_edit->text().toStdString();
        auto soclu = soclu_edit->text().toStdString();
        auto pret = stod(pret_edit->text().toStdString());
        try{
            this->srv.add_placa(nume, soclu, pret);
            load_data();
        } catch (...) {}
    });

    QObject::connect(lst_procesoare, &QListWidget::itemSelectionChanged, [&](){
        auto index = lst_procesoare->selectionModel()->currentIndex().row();
        if(index >= this->srv.get_proc().size())
            return;
        procesor_curent = this->srv.get_proc().at(index);
    });
    QObject::connect(filtreaza_btn, &QPushButton::clicked, [&]() {
        if(lst_procesoare->selectedItems().size() != 0) {
            auto res = this->srv.filter_placi(procesor_curent.get_soclu());
            load_data_placi(res);
        }
    });
    QObject::connect(calculeaza_btn, &QPushButton::clicked, [&]() {
        if(lst_procesoare->selectedItems().size() != 0 && lst_placi->selectedItems().size() != 0) {
            auto res = placa_curenta.get_pret() + procesor_curent.get_pret();
            QMessageBox::warning(nullptr, "Plata", QString::fromStdString(std::to_string(res) + "euro in total"));
        }
    });
    QObject::connect(lst_placi, &QListWidget::itemSelectionChanged, [&]() {
        auto index = lst_placi->selectionModel()->currentIndex().row();
        if(index >= this->srv.get_placi().size())
            return;
        placa_curenta = this->srv.get_placi().at(index);
    });
}