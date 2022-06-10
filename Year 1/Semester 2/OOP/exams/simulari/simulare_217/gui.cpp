//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "gui.h"

void Gui::init()  {
    auto *main_layout = new QVBoxLayout;

    lst = new QListWidget;
    main_layout->addWidget(lst);

    auto *details = new QHBoxLayout;
    model_edit = new QLineEdit;
    an_edit = new QLineEdit;
    details->addWidget(model_edit);
    details->addWidget(an_edit);
    main_layout->addLayout(details);

    auto *btns = new QHBoxLayout;
    sort_an = new QPushButton("Sort An");
    sort_model = new QPushButton("Sort Model");
    sort_none  = new QPushButton("Nesortat");
    btns->addWidget(sort_an);
    btns->addWidget(sort_model);
    btns->addWidget(sort_none);
    main_layout->addLayout(btns);

    this->setLayout(main_layout);
}

void Gui::load_data(vector <Device> all) const{
    lst->clear();

    for(auto const& d: all) {
        auto *item = new QListWidgetItem(QString::fromStdString(d.to_string()));
        if(d.get_culoare() == "rosu")
            item->setBackground(Qt::red);
        else if(d.get_culoare() == "galben")
            item->setBackground(Qt::yellow);
        else if(d.get_culoare() == "albastru")
            item->setBackground(Qt::blue);
        lst->addItem(item);
    }
}


void Gui::connect() {
        QObject::connect(sort_model, &QPushButton::clicked, [&](){
            auto sorted = this->srv.sort_model();
            load_data(sorted);
            this->state = 1;
        });
        QObject::connect(sort_an, &QPushButton::clicked, [&](){
            auto sorted = this->srv.sort_an();
            load_data(sorted);
            this->state = 2;
        });
        QObject::connect(sort_none, &QPushButton::clicked, [&](){
            load_data(this->srv.get_all());
            this->state = 0;
        });
        QObject::connect(lst, &QListWidget::itemSelectionChanged, [&](){
            auto index = this->lst->selectionModel()->currentIndex().row();
            if (index >= this->srv.get_all().size())
                return;
            vector <Device> all;
            if (state == 0)
                all = this->srv.get_all();
            else if (state == 1)
                all = this->srv.sort_model();
            else
                all = this->srv.sort_an();

            auto device = all.at(index);
            model_edit->setText(QString::fromStdString(device.get_model()));
            an_edit->setText(QString::fromStdString(std::to_string(device.get_an())));
        });
}