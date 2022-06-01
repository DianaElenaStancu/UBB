//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#include "service.h"

using namespace std;
void Service::addSRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata) {
    Activitate activitate{titlu, descriere, tip, durata};
    Validator::validActivitate(activitate);
    repository.add(activitate);
    undoActions.push_back(std::make_unique<UndoStore>(repository, activitate));
}

void Service::removeSRV(const TypeTitlu &titlu, const TypeDescriere &descriere, const TypeTip &tip, const TypeDurata& durata) {
    Activitate activitate{titlu, descriere, tip, durata};
    Validator::validActivitate(activitate);
    repository.remove(activitate);
    undoActions.push_back(std::make_unique<UndoErase>(repository, activitate));
}

void Service::modifySRV(const TypeTitlu & titlu, const TypeDescriere & descriere, const TypeTip& tip, const TypeDurata & durata,
                        const TypeTitlu & titlu_nou, const TypeDescriere & descriere_noua, const TypeTip& tip_nou, const TypeDurata & durata_noua) {
    Activitate activitate{titlu, descriere, tip, durata};
    Activitate activitate_noua{titlu_nou, descriere_noua, tip_nou, durata_noua};
    Validator::validActivitate(activitate);
    Validator::validActivitate(activitate_noua);
    repository.modify(activitate, activitate_noua);
    undoActions.push_back(std::make_unique<UndoModify>(repository, activitate, activitate_noua));
}

void Service::modifySRV1(const TypeTitlu & titlu, const TypeDescriere & descriere_noua, const TypeTip& tip_nou, const TypeDurata & durata_noua) {
    Activitate activitate_noua{titlu, descriere_noua, tip_nou, durata_noua};
    Validator::validActivitate(activitate_noua);
    Activitate activitate = findSRV(titlu);
    repository.modify(activitate, activitate_noua);
    undoActions.push_back(std::make_unique<UndoModify>(repository, activitate, activitate_noua));
}

Activitate Service::findSRV(const TypeTitlu& titlu) {
    Validator::validTitlu(titlu);
    auto lista = repository.getAll();
    auto it = find_if(lista.begin(), lista.end(), [&](Activitate &a){return a.getTitlu() == titlu;});
    if (it == lista.end())
        throw ServiceException("Activitate inexistenta!");
    return *it;
}

vector<Activitate> Service::filterDescriere(const TypeDescriere & descriere) {
    Validator::validDescriere(descriere);
    vector<Activitate> result{};
    auto tot = repository.getAll();
    copy_if(tot.begin(), tot.end(), back_inserter(result), [&](Activitate& a){return a.getDescriere() == descriere;});
    return result;
}

vector<Activitate> Service::filterTip(const TypeTip & tip) {
    Validator::validTip(tip);
    vector<Activitate> result{};
    auto tot = repository.getAll();
    copy_if(tot.begin(), tot.end(), back_inserter(result), [&](Activitate& a){return a.getTip() == tip;});
    return result;
}


vector<Activitate> Service::sortTitlu() {
    auto sorted{ getAll() };
    sort(sorted.begin(), sorted.end(), [](Activitate &a, Activitate &b){return a.getTitlu() < b.getTitlu();});
    return sorted;
}

vector<Activitate> Service::sortDescriere() {
    auto sorted{ getAll() };
    sort(sorted.begin(), sorted.end(), [](Activitate &a, Activitate &b){return a.getDescriere() < b.getDescriere();});
    return sorted;
}

vector<Activitate> Service::sortTipDurata() {
    auto sorted{ getAll() };
    sort(sorted.begin(), sorted.end(), [](Activitate &a, Activitate &b){return a.getTip() < b.getTip() || (a.getTip() == b.getTip() && a.getDurata() < b.getDurata());});
    return sorted;
}

const vector<Activitate>& Service::getAll() const noexcept {
    return repository.getAll();
}

void Service::golesteLista() {
    listaActivitati.clear();
    cosActivitati.clear();
}
void Service::adaugaActivitate(const TypeTitlu &titlu) {
    Activitate a = findSRV(titlu);
    listaActivitati.push_back(a);
    cosActivitati.append(a);
}

vector<Activitate> Service::getLista() {
    return listaActivitati;
}

void Service::genereazaLista(int n) {
    cosActivitati.clear();
    listaActivitati.clear();
    auto tot = repository.getAll();
    if (tot.empty())
        throw ServiceException("Nu exista activitati!\n");
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, tot.size()-1);
    for (int i = 0; i < n; i++) {
        int rndNr = dist(mt);
        //cosActivitati.append(tot[rndNr]);
        listaActivitati.push_back(tot[rndNr]);
    }
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(listaActivitati.begin(),listaActivitati.end(), std::default_random_engine(seed));

    for (auto &a: listaActivitati) {
        cosActivitati.append(a);
    }
}

long Service::numara_activitati(int durata) {
    auto lista{ getAll() };
    auto i = count_if(lista.begin(), lista.end(), [&](Activitate &a){return a.getDurata() < durata;});
    return i;
}

void Service::exportFisier(const string& fisier) {
    ofstream out{ fisier };

    if (out.fail()) {return;}

    for (const auto& a : listaActivitati) {
        out << a;
    }

    out.close();
}

void Service::Undo() {
    if (undoActions.empty()) {
        throw ServiceException("Nu mai exista operatii de undo!\n");
    }

    std::unique_ptr<ActiuneUndo> undo = std::move(undoActions.at(undoActions.size() - 1));
    (*undo).doUndo();
    undoActions.pop_back();
}

CosActivitati& Service::getCosActivitati(){
    return this->cosActivitati;
};