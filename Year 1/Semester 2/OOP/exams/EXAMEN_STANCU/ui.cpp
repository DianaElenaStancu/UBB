//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#include "ui.h"

void Ui::init(){
    main = new QVBoxLayout;

    tabel = new QTableWidget{0, 4};
    main->addWidget(tabel);

    auto ll = new QHBoxLayout;

    auto form_l = new QFormLayout;
    id = new QLineEdit;
    descriere = new QLineEdit;
    stare = new QLineEdit;
    progr = new QLineEdit;
    form_l->addRow("id", id);
    form_l->addRow("descriere", descriere);
    form_l->addRow("stare", stare);
    form_l->addRow("progr", progr);
    add = new QPushButton("Adauga");
    form_l->addRow(add);

    ll->addLayout(form_l);

    auto form2_l = new QVBoxLayout;
    cauta = new QLineEdit;
    search = new QPushButton("Search");
    form2_l->addWidget(cauta);
    form2_l->addWidget(search);

    ll->addLayout(form2_l);

    main->addLayout(ll);

    setLayout(main);
}

void Ui::load(vector <Task> all){

    tabel->clear();
    tabel->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Id")));
    tabel->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Descriere")));
    tabel->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Stare")));
    tabel->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromStdString("Nr Prog")));

    int ind = 0;
    tabel->setRowCount(all.size());
    for (auto t : all) {
        tabel->setItem(ind,0, new QTableWidgetItem(QString::number(t.get_id())));
        tabel->setItem(ind,1, new QTableWidgetItem(QString::fromStdString(t.get_descriere())));
        tabel->setItem(ind,2, new QTableWidgetItem(QString::fromStdString(t.get_stare())));
        tabel->setItem(ind,3, new QTableWidgetItem(QString::number(t.get_programatori().size())));
        ++ind;
    }

}

void Ui::connect(){
    QObject::connect(add, &QPushButton::clicked, [&](){
        try {
            auto i = stoi(id->text().toStdString());
            auto d = descriere->text().toStdString();
            auto p = progr->text().toStdString();
            vector<string> pr;
            string v = ",";
            while (p.find(v) != string::npos) {
                string nume = p.substr(0, p.find(v));
                p.erase(0, p.find(v) + 1);
                pr.push_back(nume);
            }
            pr.push_back(p);
            auto s = stare->text().toStdString();
            try {
                //std::cout << "aici";
                srv.store(i, d, s, pr);
                load(srv.getAll());
            } catch (...) {
                QMessageBox::warning(this, "Add Warning", QString::fromStdString("id existent"));
            }
        } catch(...) {
            QMessageBox::warning(this, "Add Warning", QString::fromStdString("nu s-a putut adauga taskul"));
        }
    });

    QObject::connect(search, &QPushButton::clicked, [&]() {
        string s = cauta->text().toStdString();
        load(srv.filter(s));
    });
}