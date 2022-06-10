//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#include "gui.h"

void Gui::init() {
    mainLayout = new QVBoxLayout;

    mainList = new QListWidget;
    mainLayout->addWidget(mainList);

    auto *form  = new QFormLayout;
    nrLineEdit = new QLineEdit;
    producatorLineEdit = new QLineEdit;
    tipLineEdit = new QLineEdit;
    modelLineEdit = new QLineEdit;
    form->addRow("Nr", nrLineEdit);
    form->addRow("Producator", producatorLineEdit);
    form->addRow("Tip", tipLineEdit);
    form->addRow("Model", modelLineEdit);
    mainLayout->addLayout(form);

    auto *btn  = new QHBoxLayout;
    btnAdd = new QPushButton("Add");
    btnDel = new QPushButton("Del");
    btnModify = new QPushButton("Modify");
    btnClear = new QPushButton("Clear");
    btnUndo = new QPushButton("Undo");
    btn->addWidget(btnAdd);
    btn->addWidget(btnDel);
    btn->addWidget(btnModify);
    btn->addWidget(btnClear);
    btn->addWidget(btnUndo);
    mainLayout->addLayout(btn);

    setLayout(mainLayout);
}


void Gui::loadData() {
    mainList->clear();
    auto masini = service.getAll();
    for(auto const &m: masini) {
        mainList->addItem(QString::fromStdString(m.toString()));
    }
}
void Gui::connectSignalsToSlots() {
    Connect(mainList, &QListWidget::itemSelectionChanged, [&]() {
        auto index = this->mainList->selectionModel()->currentIndex().row();
        auto masini = this->service.getAll();
        if (index >= masini.size()){
            this->nrLineEdit->clear();
            this->producatorLineEdit->clear();
            this->tipLineEdit->clear();
            this->modelLineEdit->clear();
            return;
        }
        auto masina = masini.at(index);
        this->nrLineEdit->setText(QString::fromStdString(masina.GetNrInmatriculare()));
        this->producatorLineEdit->setText(QString::fromStdString(masina.GetProducator()));
        this->tipLineEdit->setText(QString::fromStdString(masina.GetTip()));
        this->modelLineEdit->setText(QString::fromStdString(masina.GetModel()));

        //std::cout << index << std::endl;
    });
    Connect(btnAdd, &QPushButton::clicked, [&]() {
        auto nrInmatriculare = nrLineEdit->text().toStdString();
        auto producator = producatorLineEdit->text().toStdString();
        auto tip = tipLineEdit->text().toStdString();
        auto model = modelLineEdit->text().toStdString();

        try {
            service.add(nrInmatriculare, producator, model, tip);
            loadData();
        } catch (ValidatorException &ex) {
            MsgBox(QString::fromStdString(ex.toString()));
        } catch (RepoException &ex) {
            MsgBox(QString::fromStdString(ex.toString()));
        }
    });
    Connect(btnDel, &QPushButton::clicked, [&](){
        auto nrInmatriculare = nrLineEdit->text().toStdString();
        try {
            service.del(nrInmatriculare);
            loadData();
        } catch (ValidatorException &ex) {
            MsgBox(QString::fromStdString(ex.toString()));
        } catch (RepoException &ex) {
            MsgBox(QString::fromStdString(ex.toString()));
        }
    });
    Connect(btnModify, &QPushButton::clicked, [&](){
        auto nrInmatriculare = nrLineEdit->text().toStdString();
        auto producator = producatorLineEdit->text().toStdString();
        auto tip = tipLineEdit->text().toStdString();
        auto model = modelLineEdit->text().toStdString();

        try {
            service.change(nrInmatriculare, producator, model, tip);
            loadData();
        } catch (ValidatorException &ex) {
            MsgBox(QString::fromStdString(ex.toString()));
        } catch (RepoException &ex) {
            MsgBox(QString::fromStdString(ex.toString()));
        }
    });
    Connect(btnClear, &QPushButton::clicked, [&](){
        service.clear();
        loadData();
    });

    Connect(btnUndo, &QPushButton::clicked, [&](){
        service.Undo();
        loadData();
    });

}