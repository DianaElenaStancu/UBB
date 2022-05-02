//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#ifndef LAB07_SERVICE_H
#define LAB07_SERVICE_H
#include "repository.h"
#include "validator.h"
#include "undo.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <algorithm>
#include <random>
#include <chrono>

using std::copy_if;
using std::sort;
using std::find_if;
using std::count_if;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

class Service {
private:
    Repository& repository;
    vector <Activitate> listaActivitati;
    vector<std::unique_ptr<ActiuneUndo>> undoActions;
    //const Validator
public:
    Service()=delete;
    Service(const Service&) = delete;
    explicit Service(Repository& repository) noexcept :repository(repository){};
    void addSRV(const TypeTitlu &, const TypeDescriere &, const TypeTip&, const TypeDurata &);
    void removeSRV(const TypeTitlu &, const TypeDescriere &, const TypeTip &, const TypeDurata&);
    void modifySRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata,
                   const TypeTitlu & titlu_nou, const TypeDescriere & descriere_noua, const TypeTip& tip_nou, const TypeDurata & durata_noua);
    void modifySRV1(const TypeTitlu & titlu, const TypeDescriere & descriere_noua, const TypeTip& tip_nou, const TypeDurata & durata_noua);
    const vector<Activitate>& getAll() const noexcept;
    Activitate findSRV(const TypeTitlu& titlu);
    vector<Activitate> filterDescriere(const TypeDescriere & descriere);
    vector<Activitate> filterTip(const TypeTip & tip);
    vector<Activitate> sortTitlu();
    vector<Activitate> sortDescriere();
    vector<Activitate> sortTipDurata();

    void golesteLista();
    void adaugaActivitate(const TypeTitlu &titlu);
    vector <Activitate> getLista();
    void genereazaLista(int n);
    long numara_activitati(int durata);
    void exportFisier(const string& fisier);
    void Undo();
};


#endif //LAB07_SERVICE_H
