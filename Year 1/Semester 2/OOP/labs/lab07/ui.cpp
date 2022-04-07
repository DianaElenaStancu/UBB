//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#include "ui.h"


static void printMenu(ostream & out) {
    out<<"\tMeniu\n"
         "1. Adaugare\n"
         "2. Stergere\n"
         "3. Modificare\n"
         "4. Afisare\n"
         "5. Cauta activitate\n"
         "6. Filtrare\n"
         "7. Sortare\n"
         "8. Iesire\n";
}

static void readActivitate(istream & in, ostream& out, TypeTitlu& titlu, TypeDescriere& descriere, TypeTip& tip, TypeDurata& durata) {
    string strdurata;

    out<<"Introduceti titlul activitatii: ";
    std::getline(in>>std::ws, titlu);

    out<<"Introduceti descrierea activitatii: ";
    std::getline(in>>std::ws, descriere);

    out<<"Introduceti tipul: "; in>>tip;

    out<<"Introduceti durata: ";
    in>>strdurata;
    try{ durata = std::stoi(strdurata); }
    catch(...) { out<<"Durata invalida!\n";  durata=0;}
}

static void writeActivitate(ostream & out, const Activitate & activitate) {
    /*out<<"Titlu: "<<activitate.getTitlu()<<'\n';
    out<<"Descriere: "<<activitate.getDescriere()<<'\n';
    out<<"Tip: "<<activitate.getTip()<<'\n';
    out<<"Durata: "<<activitate.getDurata()<<'\n';*/
    out << "-----" << activitate << '\n';
}

void ConsoleUI::adauga(istream & in, ostream & out) {
    TypeTitlu titlu;
    TypeDescriere descriere;
    TypeTip tip;
    TypeDurata durata;
    readActivitate(in, out, titlu, descriere, tip, durata);
    try{service.addSRV(titlu, descriere, tip, durata);}
    catch(Exception& me) { out<<me; return;}
    out<<"Operatie efectuata cu succes!\n";
}

void ConsoleUI::sterge(istream &in, ostream &out) {
    TypeTitlu titlu;
    TypeDescriere descriere;
    TypeTip tip;
    TypeDurata durata;
    readActivitate(in, out, titlu, descriere, tip, durata);
    try{service.removeSRV(titlu, descriere, tip, durata);}
    catch(Exception& me) { out<<me; return;}
    out<<"Operatie efectuata cu succes!\n";
}

void ConsoleUI::modifica(istream & in, ostream & out) {
    TypeTitlu titlu, titlu_nou;
    TypeDescriere descriere, descriere_noua;
    TypeTip tip, tip_nou;
    TypeDurata durata, durata_noua;
    readActivitate(in, out, titlu, descriere, tip, durata);
    readActivitate(in, out, titlu_nou, descriere_noua, tip_nou, durata_noua);
    try{ service.modifySRV(titlu, descriere, tip, durata,
                           titlu_nou, descriere_noua, tip_nou, durata_noua);}
    catch(Exception& me) { out<<me; return;}
    out<<"Operatie efectuata cu succes!\n";
}

void ConsoleUI::afisare(ostream & out) {
    auto lista = service.getAll();
    if(lista.size() == 0) out<<"Nu exista astfel de elemente!\n";
    for(const auto& elem : lista)
        writeActivitate(out, elem);
}

void ConsoleUI::cauta(istream & in, ostream & out) {
    TypeTitlu titlu;
    out<<"Introduceti titlul activitatii: ";
    in >> titlu;
    Activitate activitate;
    try{ activitate = service.findSRV(titlu);}
    catch(Exception& me) { out<<me; return;}
    writeActivitate(out, activitate);
}

void ConsoleUI::filtrare(istream & in, ostream & out) {
    out<<"Introduceti filtrul(descriere/tip): ";
    string cmd;
    in>>cmd;
    if(cmd == "descriere"){
        TypeDescriere descriere;
        out<<"Introduceti descriere: "; in >> descriere;
        DynamicArray<Activitate> rez{};
        try{rez = service.filterDescriere(descriere); }
        catch(Exception& me) { out<<me; return;}
        if(rez.size() == 0) out<<"Nu exista astfel de elemente!\n";
        for(const auto& elem : rez)
            writeActivitate(out, elem);
    }
    else if(cmd == "tip"){
        TypeTip tip;
        out<<"Introduceti tipul: "; in >>tip;
        DynamicArray<Activitate> rez{};
        try{rez = service.filterTip(tip); }
        catch(Exception& me) { out<<me; return;}
        if(rez.size() == 0) out<<"Nu exista astfel de elemente!\n";
        for(const auto& elem : rez)
            writeActivitate(out, elem);
    }
    else out<<"Filtru invalid!\n";
}

void ConsoleUI::sortare(istream & in, ostream & out) {
    out<<"\tSortati dupa:\n"
         "1. Titlu\n"
         "2. Descriere\n"
         "3. Tip si durata\n";
    string cmd; in>>cmd;

    DynamicArray<Activitate> rez{};
    if(cmd=="1") {
        try{rez = service.sortTitlu(); }
        catch(Exception& me) { out<<me; return;}
    }
    else if(cmd == "2"){
        try{rez = service.sortDescriere(); }
        catch(Exception& me) { out<<me; return;}

    }
    else if(cmd == "3"){
        try{rez = service.sortTipDurata(); }
        catch(Exception& me) { out<<me; return;}
    }
    else {
        out<<"Optiune invalida!\n";
        return;
    }
    if(rez.size() == 0) out<<"Nu exista astfel de elemente!\n";
    for(const auto& elem : rez)
        writeActivitate(out, elem);
}

void ConsoleUI::run(istream & in, ostream & out) {
    while (true){
        printMenu(out);
        out<<"\nIntroduceti comanda: ";
        string cmd;
        in>>cmd;
        if(cmd=="1") adauga(in, out);
        else if(cmd=="2") sterge(in, out);
        else if(cmd=="3") modifica(in, out);
        else if(cmd=="4") afisare(out);
        else if(cmd=="5") cauta(in, out);
        else if(cmd=="6") filtrare(in, out);
        else if(cmd=="7") sortare(in, out);
        else if(cmd=="8") break;
        else out<<"Comanda invalida!\n";
    }
}