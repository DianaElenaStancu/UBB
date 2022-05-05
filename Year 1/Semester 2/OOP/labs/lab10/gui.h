
#ifndef LAB10_GUI_H
#define LAB10_GUI_H

#include "service.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <qmessagebox.h>
#include <QtWidgets/qcombobox.h>
#include <QTWidgets/qgridlayout.h>
#include <string>

#define Connect QObject::connect
#define MsgBox(msg) QMessageBox::information(this, "Info", msg);

class GUI : public QWidget{
private:
    Service& service;

    QListWidget *lst = new QListWidget;
    QListWidget *buttons = new QListWidget;
    QVBoxLayout *btns = new QVBoxLayout;

    QLineEdit *Titlu = new QLineEdit;
    QLineEdit *Descriere = new QLineEdit;
    QLineEdit *Tip = new QLineEdit;
    QLineEdit *Durata = new QLineEdit;
    QLineEdit *Search = new QLineEdit;

    QPushButton *btn;
    QPushButton *btnAdd = new QPushButton("&Add");
    QPushButton *btnModify = new QPushButton("&Modify");
    QPushButton *btnRemove = new QPushButton("&Remove");
    QPushButton *btnShow = new QPushButton("&Show All");
    QPushButton *btnClear = new QPushButton("&Clear");
    QPushButton *btnSearch = new QPushButton("&Cauta");
    QPushButton *btnUndo = new QPushButton("&Undo");

    QPushButton *btnNotShow = new QPushButton("&Show activitati");
    QPushButton *btnNotAdd = new QPushButton("&Adauga activitate");
    QPushButton *btnNotGen = new QPushButton("&Genereaza activitati");
    QSpinBox *spinBox = new QSpinBox;
    QPushButton *btnNotClear = new QPushButton("&Sterge activitatile");
    QPushButton *btnNotExportFisier = new QPushButton("&Exporta HTML/CSV");
    QLineEdit *Path = new QLineEdit;

    QPushButton *btnFilter = new QPushButton("&Filtrare");
    QComboBox *cmbFilter = new QComboBox;

    QPushButton *btnSort = new QPushButton("&Sortare");
    QComboBox *cmbSort = new QComboBox;

    QHBoxLayout *htable;
    QWidget *panel1, *panel2, *panel3;
    QVBoxLayout *p1l, *p2l, *p3l;

    QVector<QPushButton*> buttons_f;

    // constructor methods
    void initGUI(){

        // horizontal table
        htable = new QHBoxLayout;
        panel1 = new QWidget;
        panel2 = new QWidget;
        panel3 = new QWidget;
        htable->addWidget(panel1);
        htable->addWidget(panel2);
        htable->addWidget(panel3);
        p1l = new QVBoxLayout(panel1);
        p2l = new QVBoxLayout(panel2);
        p3l = new QVBoxLayout(panel3);
        panel1->setLayout(p1l);
        panel2->setLayout(p2l);
        panel3->setLayout(p3l);
        setLayout(htable); /// !

        // panel 1
        p1l->addWidget(lst);
        auto *buttonsL = new QHBoxLayout;
        buttonsL->addWidget(btnRemove);
        buttonsL->addWidget(btnShow);
        p1l->addLayout(buttonsL);
        auto *filterL = new QHBoxLayout;
        filterL->addWidget(btnFilter);
        cmbFilter->addItem("Descriere");
        cmbFilter->addItem("Tip");
        filterL->addWidget(cmbFilter);
        p1l->addLayout(filterL);
        auto *sortL = new QHBoxLayout;
        sortL->addWidget(btnSort);
        cmbSort->addItem("Titlu");
        cmbSort->addItem("Descriere");
        cmbSort->addItem("Tip + Durata");
        sortL->addWidget(cmbSort);
        p1l->addLayout(sortL);

        // panel 2
        auto *card = new QFormLayout;
        card->addRow("Titlu", Titlu);
        card->addRow("Descriere", Descriere);
        card->addRow("Tip", Tip);
        card->addRow("Durata", Durata);
        p2l->addLayout(card);
        auto *buttonsR = new QHBoxLayout;
        buttonsR->addWidget(btnAdd);
        buttonsR->addWidget(btnModify);
        buttonsR->addWidget(btnUndo);
        buttonsR->addWidget(btnClear);
        p2l->addLayout(buttonsR);
        auto *search = new QHBoxLayout;
        QLabel *srclabel = new QLabel("Cauta/filtreaza");
        search->addWidget(srclabel);
        search->addWidget(Search);
        search->addWidget(btnSearch);
        p2l->addLayout(search);
        p2l->addStretch();

        //notificari
        auto *notL1 = new QHBoxLayout;
        notL1->addWidget(btnNotShow);
        notL1->addWidget(btnNotAdd);
        notL1->addWidget(btnNotClear);
        p2l->addLayout(notL1);
        auto *notL2 = new QHBoxLayout;
        notL2->addWidget(btnNotGen);
        notL2->addWidget(spinBox);
        p2l->addLayout(notL2);
        auto *notL3 = new QHBoxLayout;
        QLabel *lblPath = new QLabel("Nume fisier");
        notL3->addWidget(lblPath);
        notL3->addWidget(Path);
        notL3->addWidget(btnNotExportFisier);
        p2l->addLayout(notL3);

        p3l->addLayout(btns);
    }

    void loadData(const vector <Activitate> &l){
        lst -> clear();
        for(const auto& a : l)
            lst->addItem(QString::fromStdString(a.toString()));
    }
    /*void loadButtons() {
        vector <string> tipuri;
        for (const auto& activitate: service.getAll()) {
            auto it = find_if(tipuri.begin(),tipuri.end(), [&](const string &t){return t == activitate.getTip() ;});//activitate.getTip() == a.getTip();
            if (it == tipuri.end()) {
                tipuri.push_back(activitate.getTip());
            }
        }

        if ( btns->layout() != NULL ) {
            QLayoutItem* item;
            while ( ( item = btns->layout()->takeAt( 0 ) ) != NULL )
            {
                delete item->widget();
                delete item;
            }
        }
        for(const auto& tip: tipuri) {
            btn = new QPushButton(QString::fromStdString(tip));
            btn->setObjectName(QString::fromStdString(tip));

            Connect(btn, &QPushButton::clicked, [&]() {
                auto const s = btn->objectName();
                //std::cout << s.toStdString() << std::endl;

                MsgBox(s);
            });
            btns->addWidget(btn);
        }
    }*/
    void loadButtons() {
        vector <string> tipuri;
        for (const auto& activitate: service.getAll()) {
            auto it = find_if(tipuri.begin(),tipuri.end(), [&](const string &t){return t == activitate.getTip() ;});//activitate.getTip() == a.getTip();
            if (it == tipuri.end()) {
                tipuri.push_back(activitate.getTip());
            }
        }

        if ( btns->layout() != NULL ) {
            QLayoutItem* item;
            while ( ( item = btns->layout()->takeAt( 0 ) ) != NULL )
            {
                delete item->widget();
                delete item;
            }
        }

        buttons_f.clear();

        for(const auto& tip: tipuri) {
            QPushButton* btn = new QPushButton(QString::fromStdString(tip));
            btn->setObjectName(QString::fromStdString(tip));
            buttons_f.push_back(btn);
        }

        for(auto& btn : buttons_f) {
            Connect(btn, &QPushButton::clicked, [&]() {
                auto const s = service.filterTip(btn->objectName().toStdString()).size();


                MsgBox(QString::number(s));
            });
            btns->addWidget(btn);
        }
    }

    void init_connect() {
        //butoane helper
        Connect(btnShow, &QPushButton::clicked, [&]() { loadData(service.getAll()); });
        Connect(btnClear, &QPushButton::clicked, [&]() {
            Titlu->setText("");
            Descriere->setText("");
            Tip->setText("");
            Durata->setText("");
        });
        // lista
        Connect(lst, &QListWidget::itemSelectionChanged, [&]() {
            if (lst->selectedItems().isEmpty()) {
                //daca nu e nimic selectat golesc campurile
                btnClear->animateClick();
                return;
            }
            /*auto *currentItem = lst->selectedItems().at(0);
            Activitate activitate = activitate.fromString(currentItem->text().toStdString());
            Titlu->setText(QString::fromStdString(activitate.getTitlu()));
            Descriere->setText(QString::fromStdString(activitate.getDescriere()));
            Tip->setText(QString::fromStdString(activitate.getTip()));
            Durata->setText(QString::fromStdString(std::to_string(activitate.getDurata())));*/
        });

        //butoane CRUD
        Connect(btnAdd, &QPushButton::clicked, [&](){
            auto titlu = Titlu->text().toStdString();
            auto descriere = Descriere->text().toStdString();
            auto tip = Tip->text().toStdString();
            auto durata = Durata->text().toInt();
            try {
                service.addSRV(titlu, descriere, tip, durata);
                loadData(service.getAll());
                loadButtons();
            }
            catch(Exception& me) { MsgBox(me.what()); }
        });

        Connect(btnRemove, &QPushButton::clicked, [&](){
            auto titlu = Titlu->text().toStdString();
            auto descriere = Descriere->text().toStdString();
            auto tip = Tip->text().toStdString();
            auto durata = Durata->text().toInt();
            try {
                service.removeSRV(titlu, descriere, tip, durata);
                loadData(service.getAll());
                loadButtons();
            }
            catch(Exception& me) { MsgBox(me.what()); }
        });

        Connect(btnModify, &QPushButton::clicked, [&](){
            auto titlu = Titlu->text().toStdString();
            auto descriere = Descriere->text().toStdString();
            auto tip = Tip->text().toStdString();
            auto durata = Durata->text().toInt();
            try {
                service.modifySRV1(titlu, descriere, tip, durata);
                loadData(service.getAll());
                loadButtons();
            }
            catch(Exception& me) { MsgBox(me.what()); }
        });

        Connect(btnSearch, &QPushButton::clicked, [&](){
            auto text = Search->text().toStdString();//.toInt();
            try{
                Activitate l = service.findSRV(text);
                for(int i=0; i<lst->count();++i)
                    if(lst->item(i)->text().toStdString() == l.toString())
                        lst->setCurrentRow(i);
            }
            catch(Exception& me) { MsgBox(me.what()); }
        });

        Connect(btnFilter, &QPushButton::clicked, [&](){
            try{
                auto text = Search->text();
                if(cmbFilter->currentText() == "Tip")
                {
                    vector <Activitate> activitati = service.filterTip(text.toStdString());
                    loadData(activitati);
                }
                else if(cmbFilter->currentText() == "Descriere")
                {
                    vector <Activitate> activitati = service.filterDescriere(text.toStdString());
                    loadData(activitati);
                }
            }
            catch(Exception& me) {QMessageBox::information(this, "Eroare", me.what());}
        });
        Connect(btnSort, &QPushButton::clicked, [&](){
            if(cmbSort->currentText() == "Titlu")
            {
                vector <Activitate> activitati = service.sortTitlu();
                loadData(activitati);
            }
            else if(cmbSort->currentText() == "Descriere")
            {
                vector <Activitate> activitati = service.sortDescriere();
                loadData(activitati);
            }
            else if(cmbSort->currentText() == "Tip + Durata")
            {
                vector <Activitate> activitati = service.sortTipDurata();
                loadData(activitati);
            }
        });
        Connect(btnUndo, &QPushButton::clicked, [&](){
            try{
                service.Undo();
                loadData(service.getAll());
                loadButtons();
            }
            catch(Exception& me) {QMessageBox::information(this, "Eroare", me.what());}
        });

        //lista activitati
        Connect(btnNotShow, &QPushButton::clicked, [&](){
            vector <Activitate> lista_activitati = service.getLista();
            loadData(lista_activitati);
        });
        Connect(btnNotAdd, &QPushButton::clicked, [&](){
            TypeTitlu titlu = Titlu->text().toStdString();
            try {
                service.adaugaActivitate(titlu);
                vector <Activitate> lista_activitati = service.getLista();
                loadData(lista_activitati);
            }
            catch(Exception& me) { MsgBox(me.what()); }
        });
        Connect(btnNotClear, &QPushButton::clicked, [&](){
            service.golesteLista();
            loadData(service.getAll());
            MsgBox("Lista de notificari a fost stearsa!");
        });
        Connect(btnNotGen, &QPushButton::clicked, [&](){
            int nr = spinBox->value();
            try{
                service.genereazaLista(nr);
                vector <Activitate> lista_activitati = service.getLista();
                loadData(lista_activitati);
            }
            catch(Exception& me) { MsgBox(me.what());}
        });
        Connect(btnNotExportFisier, &QPushButton::clicked, [&](){
            string fisier = Path->text().toStdString();
            if (fisier.length() <= 4 || (fisier.find(".html") == string::npos && fisier.find(".csv") == string::npos)) {
                MsgBox("Nume fisier invalid!");
                return;
            }
            service.exportFisier(fisier);
            MsgBox("Export HTML/CSV cu succes!");
        });
    }

public:
    explicit GUI(Service& srv) : service{srv} {
        initGUI();
        loadData(service.getAll());
        init_connect();
    }

};

#endif //LAB10_GUI_H