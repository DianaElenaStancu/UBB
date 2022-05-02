//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#include "ui.h"
#include <fstream>
std::ifstream fin("file.txt");

static void printMenu(ostream & out) {
    out<<"\tMeniu\n"
         "1. Adaugare\n"
         "2. Stergere\n"
         "3. Modificare\n"
         "4. Afisare\n"
         "5. Cauta activitate\n"
         "6. Filtrare\n"
         "7. Sortare\n"
         "8. Lista de activitati\n"
         "9. Undo\n"
         "0. Iesire\n";
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
    if(lista.empty()) out<<"Nu exista astfel de elemente!\n";
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
        vector<Activitate> rez{};
        try{rez = service.filterDescriere(descriere); }
        catch(Exception& me) { out<<me; return;}
        if(rez.empty()) out<<"Nu exista astfel de elemente!\n";
        for(const auto& elem : rez)
            writeActivitate(out, elem);
    }
    else if(cmd == "tip"){
        TypeTip tip;
        out<<"Introduceti tipul: "; in >>tip;
        vector<Activitate> rez{};
        try{rez = service.filterTip(tip); }
        catch(Exception& me) { out<<me; return;}
        if(rez.empty()) out<<"Nu exista astfel de elemente!\n";
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

    vector<Activitate> rez{};
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
    if(rez.empty()) out<<"Nu exista astfel de elemente!\n";
    for(const auto& elem : rez)
        writeActivitate(out, elem);
}

void ConsoleUI::lista_activitati(istream & in, ostream & out)  {
    out<<"\tMeniu lista activitati:\n"
         "1. Goleste lista\n"
         "2. Adauga in lista\n"
         "3. Genereaza lista\n"
         "4. Exporta lista\n";
    string cmd; in>>cmd;
    if (cmd == "1") {
        service.golesteLista();
        out << "Golire cu succes!";
    } else if (cmd == "2") {
        string titlu;
        out<<"Introduceti titlu: "; in >> titlu;
        try{service.adaugaActivitate(titlu); }
        catch(Exception& me) { out<<me; return;}
    } else if (cmd == "3") {
        string nstr; int n;
        out << "Introduceti numarul de activitati: "; in >> nstr;
        try{ n = std::stoi(nstr); }
        catch(...) { out<<"Valoare invalida!\n"; return;}
        if (n <= 0 && n >= 20) {
            out << "Valoare invalida!\n";
            return;
        }
        try {service.genereazaLista(n);}
        catch(Exception& me) {out << me; return;}

    } else if (cmd == "4") {
        string fisier;
        cout << "Fisier export: ";
        cin >> fisier;
        if (fisier.length() <= 4 || (fisier.find(".html") == string::npos && fisier.find(".csv") == string::npos)) {
            cout << "Nume fisier invalid!\n";
            return;
        }
        service.exportFisier(fisier);
    }
    else {
        out << "Optiune invalida\n";
        return;
    }
    vector <Activitate> rez = service.getLista();
    for (auto &a: rez)
        out << a << '\n';
    out << "Numar activitati: " << rez.size() << '\n';
}

void ConsoleUI::numara_activitati(istream & in, ostream & out)  {
    string strdurata; int durata;
    out<<"Introduceti durata: ";
    in>>strdurata;
    try{ durata = std::stoi(strdurata); }
    catch(...) { out<<"Durata invalida!\n";  durata=0;}
    out << service.numara_activitati(durata) << '\n';
}

void ConsoleUI::undo(ostream & out) {
    try {
        service.Undo();
    }
    catch(Exception& me) {out << me;}
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
        else if(cmd=="8") lista_activitati(in, out);
        else if(cmd=="9") undo(out);
        else if(cmd=="0") break;
        else out<<"Comanda invalida!\n";
    }
}

void ConsoleUI::run_file(ostream & out) {
    vector <string> lista; string cmd;
    while(fin >> cmd) {
        lista.push_back(cmd);
    }
    for (auto &c: lista) {
        string copie=c;
        string input=c.substr(0, c.find(":"));
        auto pos = c.find(input);
        c.erase(pos, input.size() + 1);
        if (input == "add") {
            TypeTitlu titlu;
            TypeDescriere descriere;
            TypeTip tip;
            TypeDurata durata_int; string durata;

            titlu=c.substr(0, c.find(";"));
            c.erase(0, titlu.size() + 1);

            descriere=c.substr(0, c.find(";"));
            c.erase(0, descriere.size() + 1);

            tip=c.substr(0, c.find(";"));
            c.erase(0, tip.size() + 1);

            durata=c.substr(0, c.find(";"));
            c.erase(0, durata.size() + 1);

            try{ durata_int = std::stoi(durata); }
            catch(...) { out<<"Durata invalida!\n";  durata_int=0;}

            if(c.empty()) {
                try { service.addSRV(titlu, descriere, tip, durata_int); }
                catch (Exception &me) {
                    cout << "Comanda invalida: " << copie << '\n';
                    out << me;
                    cout << "*****\n";
                }
            }

        } else if (input == "delete") {
            TypeTitlu titlu;
            TypeDescriere descriere;
            TypeTip tip;
            TypeDurata durata_int; string durata;

            titlu=c.substr(0, c.find(";"));
            c.erase(0, titlu.size() + 1);

            descriere=c.substr(0, c.find(";"));
            c.erase(0, descriere.size() + 1);

            tip=c.substr(0, c.find(";"));
            c.erase(0, tip.size() + 1);

            durata=c.substr(0, c.find(";"));
            c.erase(0, durata.size() + 1);

            try{ durata_int = std::stoi(durata); }
            catch(...) { out<<"Durata invalida!\n";  durata_int=0;}
            if (c.empty()) {
                try{service.removeSRV(titlu, descriere, tip, durata_int);}
                catch(Exception& me) {cout << "Comanda invalida: " << copie << '\n';  out<<me; cout << "*****\n";}
            }

        } else if (input == "modify") {
            TypeTitlu titlu, titlu_new;
            TypeDescriere descriere, descriere_new;
            TypeTip tip, tip_new;
            TypeDurata durata_int, durata_int_new; string durata, durata_new;

            titlu=c.substr(0, c.find(";"));
            c.erase(0, titlu.size() + 1);

            descriere=c.substr(0, c.find(";"));
            c.erase(0, descriere.size() + 1);

            tip=c.substr(0, c.find(";"));
            c.erase(0, tip.size() + 1);

            durata=c.substr(0, c.find(";"));
            c.erase(0, durata.size() + 1);

            try{ durata_int = std::stoi(durata); }
            catch(...) { out<<"Durata invalida!\n";  durata_int=0;}

            titlu_new=c.substr(0, c.find(";"));
            c.erase(0, titlu_new.size() + 1);

            descriere_new=c.substr(0, c.find(";"));
            c.erase(0, descriere_new.size() + 1);

            tip_new=c.substr(0, c.find(";"));
            c.erase(0, tip_new.size() + 1);

            durata_new=c.substr(0, c.find(";"));
            c.erase(0, durata_new.size() + 1);

            try{ durata_int_new = std::stoi(durata_new); }
            catch(...) { out<<"Durata invalida!\n";  durata_int_new=0;}

            if(c.empty()) {
                try{ service.modifySRV(titlu, descriere, tip, durata_int,
                                       titlu_new, descriere_new, tip_new, durata_int_new);}
                catch(Exception& me) {  cout << "Comanda invalida: " << copie << '\n'; out<<me; cout << "*****\n";}
            }
        } else if (input == "print") {
            cout << "*****\n";
            auto lista = service.getAll();
            if(lista.empty()) out<<"Nu exista astfel de elemente!\n";
            for(const auto& elem : lista)
                writeActivitate(out, elem);
        } else {
            cout << "Comanda invalida: " << copie << '\n';
        }
    }
}