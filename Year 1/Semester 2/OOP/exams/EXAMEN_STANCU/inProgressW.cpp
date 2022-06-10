//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#include "inProgressW.h"



void inProgressW::init(){

    main = new QVBoxLayout;

    auto l = new QHBoxLayout;
    open = new QPushButton("open");
    closed = new QPushButton("closed");
    inprogress = new QPushButton("inprogress");
    l->addWidget(open);
    l->addWidget(closed);
    l->addWidget(inprogress);
    main->addLayout(l);
    lista = new QTableWidget{0,4};
    main->addWidget(lista);


    setLayout(main);
}

void inProgressW::load(){
    auto l = srv.inprogresst();

    lista->clear();
    lista->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Id")));
    lista->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Descriere")));
    lista->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Stare")));
    lista->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromStdString("Nr Prog")));

    int ind = 0;
    lista->setRowCount(l.size());
    for (auto t : l) {
        lista->setItem(ind,0, new QTableWidgetItem(QString::number(t.get_id())));
        lista->setItem(ind,1, new QTableWidgetItem(QString::fromStdString(t.get_descriere())));
        lista->setItem(ind,2, new QTableWidgetItem(QString::fromStdString(t.get_stare())));
        lista->setItem(ind,3, new QTableWidgetItem(QString::number(t.get_programatori().size())));
        ++ind;
    }
}

void inProgressW::connect(){

    QObject::connect(open, &QPushButton::clicked, [&](){
        if (lista->selectedItems().isEmpty()) {
            //daca nu e nimic selectat golesc campurile
            return;
        } else {
            //auto *currentItem = lst->selectedItems().at(0);
            int index = lista->selectionModel()->currentIndex().row();
            auto l = srv.inprogresst();
            auto task = l.at(index);

            //std::cout << task << std::endl;
            srv.change_stare(task, "open");
            load();
        }
    });
    QObject::connect(closed, &QPushButton::clicked, [&](){
        if (lista->selectedItems().isEmpty()) {
            //daca nu e nimic selectat golesc campurile
            return;
        } else {
            //auto *currentItem = lst->selectedItems().at(0);
            int index = lista->selectionModel()->currentIndex().row();
            auto l = srv.inprogresst();
            auto task = l.at(index);

            //cout << task << endl;
            srv.change_stare(task, "closed");
        }
    });
}