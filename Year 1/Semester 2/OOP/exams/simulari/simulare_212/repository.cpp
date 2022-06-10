//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "repository.h"

void RepoProc::load_data() {
    ifstream in(this->filename, std::ios::in);
    if (!in.is_open())
        return;
    if (in.peek() == ifstream::traits_type::eof())
        return;
    while(!in.eof()) {
        if (in.peek() == ifstream::traits_type::eof())
            return;
        Procesor proc;
        in >> proc;
        RepoProc::store(proc);
    }
}

void RepoProc::store(Procesor &proc) {
    storage.push_back(proc);
}

vector <Procesor> RepoProc::get_all() const {
    return this->storage;
}

void RepoPlaci::load_data() {
    ifstream in(this->filename, std::ios::in);
    if (!in.is_open())
        return;
    if (in.peek() == ifstream::traits_type::eof())
        return;
    while(!in.eof()) {
        if (in.peek() == ifstream::traits_type::eof())
            return;
        PlacaDeBaza placa;
        in >> placa;
        RepoPlaci::store(placa);
    }
}

void RepoPlaci::write_to_file() {
    ofstream out(this->filename, std::ios::trunc);
    if (!out.is_open())
        return;
    for (auto& p: get_all())
        out << p;
}

bool RepoPlaci::exista(const PlacaDeBaza& placa) const {
    auto index = std::find_if(this->storage.begin(), this->storage.begin(), [&placa](const PlacaDeBaza& p){
        return p == placa;
    });
    if (index == storage.end())
        return false;
    return true;
}

void RepoPlaci::store(PlacaDeBaza &placa) {
    if (!exista(placa)) {
        storage.push_back(placa);
        write_to_file();
    }
}

vector <PlacaDeBaza> RepoPlaci::get_all() const {
    return this->storage;
}