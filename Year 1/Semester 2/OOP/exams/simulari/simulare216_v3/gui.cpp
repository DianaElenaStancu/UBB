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

    tbl->clear();
    int nbOfItems = 0;
    tbl->setHorizontalHeaderItem(0, new QTableWidgetItem("Nume"));
    tbl->setHorizontalHeaderItem(1, new QTableWidgetItem("Tara"));
    tbl->setHorizontalHeaderItem(2, new QTableWidgetItem("Puncte"));
    tbl->setHorizontalHeaderItem(3, new QTableWidgetItem("Rank"));
    tbl->setRowCount(all.size());
    for(const auto& a : all) {
        // tbl->addItem(QString::fromStdString(a.toString()));
        tbl->setVerticalHeaderItem(nbOfItems, new QTableWidgetItem(QString::number(nbOfItems)));
        QTableWidgetItem* curent_item = new QTableWidgetItem(QString::fromStdString(a.get_nume()));
        curent_item->setBackground(Qt::red);
        curent_item->setData(Qt::UserRole, nbOfItems);
        tbl->setItem(nbOfItems, 0, curent_item);
        tbl->setItem(nbOfItems, 1, new QTableWidgetItem(QString::fromStdString(a.get_tara())));
        tbl->setItem(nbOfItems, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(a.get_puncte()))));
        tbl->setItem(nbOfItems, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(a.get_rank()))));
        nbOfItems++;
    }
}


void Gui::init() {
    auto *main_layout = new QVBoxLayout;

    lst = new QListWidget;
    main_layout->addWidget(lst);

    tbl = new QTableWidget(0, 4);

    main_layout->addWidget(tbl);

    auto *edits = new QFormLayout;
    nume_edit = new QLineEdit;
    tara_edit = new QLineEdit;
    rank_spin = new QSpinBox;
    adauga_btn = new QPushButton("Adauga");
    qualified = new QCheckBox("Qualified", nullptr);
    edits->addRow("Nume", nume_edit);
    edits->addRow("Tara", tara_edit);
    edits->addRow(rank_spin, adauga_btn);
    edits->addWidget(qualified);
    main_layout->addLayout(edits);

    this->setLayout(main_layout);
}

void Gui::connect() {
    QObject::connect(adauga_btn, &QPushButton::clicked, [&](){
        if (nume_edit->text().isEmpty() || tara_edit->text().isEmpty())
            return;
        auto nume = nume_edit->text().toStdString();
        auto tara = tara_edit->text().toStdString();
        auto rank = rank_spin->value();
        auto all = this->srv.get_all();
        auto index = std::find_if(all.begin(), all.end(), [&rank](Jucator &j){
            return j.get_rank() == rank;
        });
        if (index != all.end()) {
            QMessageBox::warning(nullptr, "Info adauga", QString::fromStdString("rank deja existent"));
            return;
        }
        this->srv.adauga(nume, tara, rank);
        load_data();
    });
    QObject::connect(qualified, &QCheckBox::clicked, [&](){
        if (qualified->isChecked()) {
            lst->clear();
            auto all = this->srv.get_all();
            for (const auto& j: all) {
                auto *item = new QListWidgetItem(QString::fromStdString(j.to_string()));
                if(j.get_puncte() >= 250)
                    item->setBackground(Qt::green);
                lst->addItem(item);
            }
        } else {
            lst->clear();
            auto all = this->srv.get_all();
            for (const auto& j: all) {
                auto *item = new QListWidgetItem(QString::fromStdString(j.to_string()));
                lst->addItem(item);
            }
        }
    });
}