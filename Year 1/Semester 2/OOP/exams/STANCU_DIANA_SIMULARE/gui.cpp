//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "gui.h"
#include <iostream>
void Gui::load_data(vector <Elev> all) {
    lst->clear();
    for(auto but :buttons_f){
        btns_del->removeWidget(but);
        delete but;
    }
    buttons_f.clear();
    for (auto const& e: all) {
        auto *item = new QListWidgetItem(QString::fromStdString(e.to_string()));
        if(e.get_medie() <= 5) {
            item->setBackground(Qt::red);
        } else if (e.get_medie() > 5 && e.get_medie() < 9) {
            item->setBackground(Qt::yellow);
        } else
            item->setBackground(Qt::green);
        lst->addItem(item);

        auto btn = new QPushButton(QString::fromStdString(e.get_cod()));
        buttons_f.push_back(btn);
    }

    for(auto btn: buttons_f) {
        btns_del->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, [=](){

            auto text = btn->text().toStdString();
            auto lista = srv.get_all();
            auto it = find_if(lista.begin(), lista.end(), [=](Elev &e){
                return e.get_cod() == text;
            });

        QMessageBox* box=new QMessageBox;
        box->setText("Do you want to delete?");
        box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        auto ret=box->exec();
        switch(ret){
            case QMessageBox::Yes:
                srv.erase(*it);
                btns_del->removeWidget(btn);
                load_data(srv.get_all());
                break;
            case QMessageBox::No:
                box->close();
                break;
            default:
                box->close();
                break;
        }
        });
    }

}

void Gui::init() {
    auto *main_layout = new QVBoxLayout;

    auto *panel = new QHBoxLayout;
    lst = new QListWidget;
    btns_del = new QVBoxLayout;
    panel->addWidget(lst);
    panel->addLayout(btns_del);
    main_layout->addLayout(panel);

    auto *form = new QFormLayout;
    nume_edit = new QLineEdit;
    prenume_edit = new QLineEdit;
    clasa_edit = new QLineEdit;
    medie_edit = new QLineEdit;
    form->addRow("Nume", nume_edit);
    form->addRow("Prenume", prenume_edit);
    form->addRow("Clasa", clasa_edit);
    form->addRow("Medie", medie_edit);
    main_layout->addLayout(form);

    auto *btns = new QHBoxLayout;
    sortat_clasa_btn = new QPushButton("Sort Clasa");
    sortat_medie_btn = new QPushButton("Sort Medie");
    sortat_nume_btn = new QPushButton("Sort Nume");
    nesortat_btn = new QPushButton("NeSort");
    btns->addWidget(sortat_clasa_btn);
    btns->addWidget(sortat_medie_btn);
    btns->addWidget(sortat_nume_btn);
    btns->addWidget(nesortat_btn);
    main_layout->addLayout(btns);

    this->setLayout(main_layout);
}

void Gui::clear_edits() {
    nume_edit->clear();
    prenume_edit->clear();
    medie_edit->clear();
    clasa_edit->clear();
}

void Gui::connect(){
    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&](){
        auto index = lst->selectionModel()->currentIndex().row();
        auto all = this->srv.get_all();
        if (index >= all.size())
            return;
        auto elev = all.at(index);
        nume_edit->setText(QString::fromStdString(elev.get_nume()));
        prenume_edit->setText(QString::fromStdString(elev.get_prenume()));
        clasa_edit->setText(QString::number(elev.get_clasa()));
        medie_edit->setText(QString::number(elev.get_medie()));
    });
    QObject::connect(sortat_clasa_btn, &QPushButton::clicked, [&](){
        clear_edits();
        auto res = srv.sort_clasa();
        load_data(res);
    });
    QObject::connect(sortat_medie_btn, &QPushButton::clicked, [&](){
        clear_edits();
        auto res = srv.sort_medie();
        load_data(res);
    });
    QObject::connect(sortat_nume_btn, &QPushButton::clicked, [&](){
        clear_edits();
        auto res = srv.sort_nume();
        load_data(res);
    });
    QObject::connect(nesortat_btn, &QPushButton::clicked, [&](){
        clear_edits();
        load_data(srv.get_all());
    });


}