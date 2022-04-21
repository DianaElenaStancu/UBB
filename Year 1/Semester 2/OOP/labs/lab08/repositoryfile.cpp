//
// Created by Diana-Elena Stancu on 20/04/2022.
//
#include "repositoryfile.h"

void RepositoryFile::loadFromFile() {
    ifstream in(filename, std::ios::in);

    if(!in.is_open()) {
        throw RepositoryException("Open error\n");
    }

    if(in.peek() == ifstream::traits_type::eof()) {
        return;
    }

    while(!in.eof()) {
        if(in.peek() == ifstream::traits_type::eof()) {
            return;
        }
        Activitate activitate;
        in >> activitate;
        Repository::add(activitate);
    }
}

void RepositoryFile::writeToFile(){
    ofstream out(filename, ios::trunc);

    if (!out.is_open()) {throw RepositoryException("Open error\n");}

    for (const auto& a : getAll()) {
        out << a;
    }
}

void RepositoryFile::add(const Activitate& activitate) {
    Repository::add(activitate);
    writeToFile();
}
void RepositoryFile::remove(const Activitate& activitate) {
    Repository::remove(activitate);
    writeToFile();
}
void RepositoryFile::modify(Activitate& activitate, Activitate& activitate_noua) {
    Repository::modify(activitate, activitate_noua);
    writeToFile();
}
