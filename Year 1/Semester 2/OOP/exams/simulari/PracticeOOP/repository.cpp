//
// Created by Diana-Elena Stancu on 15/05/2022.
//

#include "repository.h"

bool Repository::exista(const Masina& masina) const{
    try {
        find(masina.GetNrInmatriculare());
        return true;
    }
    catch(const RepoException) {
        return false;
    }
}
void Repository::store(const Masina& masina){
    if(exista(masina)) {
        throw RepoException("Masina deja exista!\n");
    }
    storage.push_back(masina);
}
void Repository::erase(const Masina& masina){
    auto it = std::find_if(this->storage.begin(), this->storage.end(),
                           [&masina](const Masina& masina1) {return masina == masina1;});
    if (it != this->storage.end()) {
        this->storage.erase(it);
    } else {
        throw RepoException("Masina inexistenta!\n");
    }
}

const Masina& Repository::find(const string& nrInmatriculare) const{
    auto it = std::find_if(this->storage.begin(), this->storage.end(),
                           [&nrInmatriculare](const Masina &masina){return masina.GetNrInmatriculare() == nrInmatriculare;});
    if (it != this->storage.end())
            return *it;
    throw RepoException("Masina inexistenta!\n");
}
void Repository::modify(const Masina& masinaModify){
    auto it = std::find_if(this->storage.begin(), this->storage.end(),
                           [&masinaModify](const Masina& masina){return masina == masinaModify;});
    if (it != this->storage.end()) {
        *it = masinaModify;
    } else {
        throw RepoException("Masina inexistenta!\n");
    }
}
const vector<Masina>& Repository::getAll() const noexcept{
    return storage;
}

const unsigned int Repository::getLength() const noexcept{
    return static_cast<unsigned int>(storage.size());
}

void Repository::clear() noexcept{
    storage.clear();
}
ostream& operator<<(ostream& out, const Repository& repo){
    for(const auto& masina: repo.storage) {
        out << masina;
    }
    return out;
}