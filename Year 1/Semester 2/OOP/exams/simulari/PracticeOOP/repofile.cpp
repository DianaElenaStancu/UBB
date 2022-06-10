//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#include "repofile.h"


void Repofile::loadFromFile() {
    ifstream in(this->filename, std::ios::in);

    if(!in.is_open()) {
        throw RepoException("open file error");
    }

    if(in.peek() == std::ifstream::traits_type::eof())
        return;

    while(!in.eof()) {
        if(in.peek() == std::ifstream::traits_type::eof())
            return;
        Masina masina;
        in >> masina;
        Repository::store(masina);
    }
}

void Repofile::writeToFile() {
    ofstream out(this->filename, std::ios::trunc);
    if (!out.is_open()) {
        throw RepoException("open error");
    }
    for (const auto &m: getAll())
        out << m;
}


void Repofile::store(const Masina& masina) {
    Repository::store(masina);
    this->writeToFile();
}
void Repofile::erase(const Masina& masina) {
    Repository::erase(masina);
    this->writeToFile();
}
void Repofile::modify(const Masina& masinaModify) {
    Repository::modify(masinaModify);
    this->writeToFile();
}