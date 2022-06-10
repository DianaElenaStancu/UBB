//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "repository.h"

void Repository::load_data() {
    ifstream in(this->filename, std::ios::in);
    if (!in.is_open())
        return;
    if (in.peek() == std::ifstream::traits_type::eof())
        return;
    while(!in.eof()) {
        Joc joc;
        in >> joc;
        Repository::store(joc);
    }
}

void Repository::store(const Joc &joc) {
    storage.push_back(joc);
}

vector <Joc> Repository::get_all() const{
    return this->storage;
}

void test_repository(){
    Repository repo{"inexistent.txt"};
    assert(repo.get_all().size() == 0);
    Repository rep1{"gol.txt"};
    assert(rep1.get_all().size() == 0);
    Repository rep2{"test.txt"};
    assert(rep2.get_all().size() == 2);
}