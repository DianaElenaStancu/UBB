//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "gui.h"

void Gui::load_data(vector <Jucator> all) {
    lst->clear();
    for (const auto& j: all) {
        lst->addItem(QString::fromStdString(j.to_string()));
    }
}


void Gui::init() {
    auto *main_layout = new QVBoxLayout;

    lst = new QListWidget;
    main_layout->addWidget(lst);

    auto *form = new QFormLayout;
    sld = new QSlider(Qt::Horizontal, nullptr);
    sld->setMinimum(1);
    sld->setMaximum(100);
    nume_edit = new QLineEdit;
    tara_edit = new QLineEdit;
    adauga_btn = new QPushButton("AAAdauga");
    form->addRow("Nume", nume_edit);
    form->addRow("Tara", tara_edit);
    form->addRow(sld);
    form->addRow(adauga_btn);
    main_layout->addLayout(form);

    btn_layout = new QHBoxLayout;
    main_layout->addLayout(btn_layout);

    generate_btn = new QPushButton("Generate");
    main_layout->addWidget(generate_btn);

    this->setLayout(main_layout);
}

void Gui::load_btns() {
    auto all = this->srv.get_all();
    vector <string> tari;
    for (auto &j: all) {
        auto index = std::find_if(tari.begin(), tari.end(), [&](string tara){
            return j.get_tara() == tara;
        });
        if (index == tari.end()) {
            tari.push_back(j.get_tara());
            auto *btn = new QRadioButton(QString::fromStdString(j.get_tara()));
            btn_lst.push_back(btn);
            btn_layout->addWidget(btn);
        }
    }
    for (auto &btn: btn_lst) {
        QObject::connect(btn, &QRadioButton::clicked, [&]() {
            auto tara = btn->text().toStdString();
            auto res = this->srv.filter(tara);
            load_data(res);
        });
    }
}

void Gui::connect() {
    QObject::connect(adauga_btn, &QPushButton::clicked, [&](){
       if (nume_edit->text().isEmpty() || tara_edit->text().isEmpty())
           return;
       auto name = nume_edit->text().toStdString();
       auto tara = tara_edit->text().toStdString();
       auto puncte = sld->value();
       try {
           this->srv.store(name, tara, puncte);
           load_data(srv.get_all());
       } catch(...) {

       }
    });
    QObject::connect(generate_btn, &QPushButton::clicked, [&](){
        auto all = this->srv.get_all();
        int size = all.size();
        srand(time(NULL));
        int r1 = rand()%size;
        int r2 = r1;
        while(r2 == r1) {
            r2 = rand()%size;
        }
        Jucator j1 = all.at(r1);
        Jucator j2 = all.at(r2);
        int s1_1 = rand()%2 + 6;
        int s1_2 = rand()%5 + 1;
        int s2_1 = rand()%2 + 6;
        int s2_2 = rand()%5 + 1;
        string scor1, scor2;
        scor1 = std::to_string(s1_1) + "-" + std::to_string(s1_2);
        scor2 = std::to_string(s2_1) + "-" + std::to_string(s2_2);
        string message;
        message = "[" + std::to_string(j1.get_rank())  + "]" + j1.get_nume() + " vs. " +
                "[" + std::to_string(j2.get_rank())  + "]" + j2.get_nume() + "\n" +
                "Scor: " + scor1  + ", " + scor2;
        QMessageBox::information(nullptr, "Meci info", QString::fromStdString(message));
    });
}