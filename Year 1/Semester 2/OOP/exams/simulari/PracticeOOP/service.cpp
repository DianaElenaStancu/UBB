//
// Created by Diana-Elena Stancu on 16/05/2022.
//
#include "service.h"

void Service::add(const string& nrInmatriculare, const string& producator, const string& model, const string& tip){
    Masina masina {nrInmatriculare, producator, model, tip};
    val.validate(masina);
    repo.store(masina);
    UndoActiune.push_back(std::make_unique<undoAdd>(repo, masina));
}
void Service::del(const string& nrInmatriculare){
    Masina masina {nrInmatriculare, "P", "M", "T"};
    val.validate(masina);
    Masina masinaVeche = repo.find(nrInmatriculare);
    repo.erase(masina);
    UndoActiune.push_back(std::make_unique<undoRemove>(repo, masinaVeche));
}
void Service::change(const string& nrInmatriculare, const string& producator, const string& model, const string& tip){
    Masina masina {nrInmatriculare, producator, model, tip};
    val.validate(masina);
    Masina masinaVeche = repo.find(nrInmatriculare);
    repo.modify(masina);
    UndoActiune.push_back(std::make_unique<undoModify>(repo, masinaVeche));
}

void Service::clear() {
    UndoActiune.push_back(std::make_unique<undoClear>(repo, repo.getAll()));
    this->repo.clear();
}
const Masina& Service::find(const string& nrInmatriculare){
    return repo.find(nrInmatriculare);
}
const vector <Masina>& Service::getAll() const noexcept{
    return repo.getAll();
}
size_t Service::getListSize() const noexcept{
    return repo.getLength();
}

vector <Masina> Service::filter(const string& filtru)  {
    auto masini = this->repo.getAll();
    vector <Masina> masini_filtered={};
    std::copy_if(masini.begin(), masini.end(), std::back_inserter(masini_filtered), [&filtru](const Masina& m){
        return (m.GetModel().find(filtru) != string::npos);
    });
    return masini_filtered;
}

void Service::Undo() {
    if(this->UndoActiune.empty())
        return;

    std::unique_ptr<undo> u = std::move(UndoActiune.at(UndoActiune.size() - 1));
    (*u).doUndo();
    UndoActiune.pop_back();
}