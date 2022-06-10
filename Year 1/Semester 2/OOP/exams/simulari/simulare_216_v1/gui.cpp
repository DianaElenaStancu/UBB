//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "gui.h"

void Gui::load_data() {
    lst->clear();
    auto all = this->srv.get_all();
    for (const auto& j: all) {
        lst->addItem(QString::fromStdString(j.to_string()));
    }
    int a = all.size();
    sld->setMinimum(1);
    sld->setMaximum(a);
}


void Gui::init() {
    auto *main_layout = new QVBoxLayout;

    lst = new QListWidget;
    main_layout->addWidget(lst);

    auto *edits = new QFormLayout;
    nume_edit = new QLineEdit;
    puncte_edit = new QLineEdit;
    edits->addRow("Nume", nume_edit);
    edits->addRow("Puncte", puncte_edit);
    main_layout->addLayout(edits);

    auto *btns = new QHBoxLayout;
    finala_btn = new QRadioButton("Finala");
    semifinala_btn = new QRadioButton("Semifinala");
    sferturi_btn = new QRadioButton("Sferturi");
    btns->addWidget(finala_btn);
    btns->addWidget(semifinala_btn);
    btns->addWidget(sferturi_btn);
    main_layout->addLayout(btns);

    recalc_btn = new QPushButton("Recalculeaza ranking");
    main_layout->addWidget(recalc_btn);

    auto *elimina = new QHBoxLayout;
    elimina_btn = new QPushButton("Elimina");
    sld = new QSlider(Qt::Horizontal ,nullptr);
    elimina->addWidget(sld);
    elimina->addWidget(elimina_btn);
    main_layout->addLayout(elimina);

    this->setLayout(main_layout);
}

void Gui::connect() {
    QObject::connect(finala_btn, &QRadioButton::clicked, [&](){
        if (nume_edit->text().isEmpty()  || puncte_edit->text().isEmpty())
            return;
        auto nume = nume_edit->text().toStdString();
        auto puncte = stoi(puncte_edit->text().toStdString());
        if (!this->srv.exista_nume(nume)) {
            QMessageBox::warning(nullptr, "Info nume", "Numele nu exista in lista!");
            return;
        }
        if (puncte <= 0) {
            QMessageBox::warning(nullptr, "Info puncte", "Puncte invalide!");
            return;
        }
        this->srv.update_puncte(nume, puncte, 0);
        load_data();
    });
    QObject::connect(semifinala_btn, &QRadioButton::clicked, [&](){
        if (nume_edit->text().isEmpty()  || puncte_edit->text().isEmpty())
            return;
        auto nume = nume_edit->text().toStdString();
        auto puncte = stoi(puncte_edit->text().toStdString());
        if (!this->srv.exista_nume(nume)) {
            QMessageBox::warning(nullptr, "Info nume", "Numele nu exista in lista!");
            return;
        }
        if (puncte <= 0) {
            QMessageBox::warning(nullptr, "Info puncte", "Puncte invalide!");
            return;
        }
        this->srv.update_puncte(nume, puncte, 1);
        load_data();
    });
    QObject::connect(sferturi_btn, &QRadioButton::clicked, [&](){
        if (nume_edit->text().isEmpty()  || puncte_edit->text().isEmpty())
            return;
        auto nume = nume_edit->text().toStdString();
        auto puncte = stoi(puncte_edit->text().toStdString());
        if (!this->srv.exista_nume(nume)) {
            QMessageBox::warning(nullptr, "Info nume", "Numele nu exista in lista!");
            return;
        }
        if (puncte <= 0) {
            QMessageBox::warning(nullptr, "Info puncte", "Puncte invalide!");
            return;
        }
        this->srv.update_puncte(nume, puncte, 2);
        load_data();
    });
    QObject::connect(recalc_btn, &QPushButton::clicked, [&]() {
        this->srv.recalc_ranking();
        load_data();
    });
    QObject::connect(elimina_btn, &QPushButton::clicked, [&]() {
       // this->srv.recalc_ranking();
        auto m = sld->value();
        if (m >= this->srv.get_all().size()) {
            QMessageBox::warning(nullptr, "Info elimina", "Nu poti elimina asa multi!");
            return;
        }
        this->srv.elimina(m);
        load_data();
    });
}