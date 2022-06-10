//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#include "repository.h"


void Repository::load_from_file() {
    ifstream in(this->filename, std::ios::in);
    if (!in.is_open())
        return;

    if (in.peek() == ifstream::traits_type::eof())
        return;

    while(!in.eof()) {
        if (in.peek() == ifstream::traits_type::eof())
            return;
        Apartament apartament;
        in >> apartament;
        Repository::store(apartament);
    }
}

bool Repository::exista(const Apartament& apartament) {
    auto it = std::find_if(storage.begin(), storage.end(), [&apartament](const Apartament &a){
        return a == apartament;
    });
    if (it != storage.end())
        return true;
    return false;
}

void Repository::store(const Apartament& apartament) {
    if (!exista(apartament)) {
        storage.push_back(apartament);
    }
}

void Repository::remove(const Apartament& apartament) {
    auto index = std::find_if(this->storage.begin(), this->storage.end(), [&](Apartament &a){
        return a == apartament;
    });
    if (index != storage.end()) {
        storage.erase(index);
    }
}

std::vector <Apartament> Repository::get_all() const {
    return this->storage;
}

void test_repository() {

}
