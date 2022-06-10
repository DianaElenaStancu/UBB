//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "repository.h"

void Repository::read_from_file() {
    ifstream in(this->filename, std::ios::in);
    if (!in.is_open())
        return;
    if (in.peek() == std::ifstream::traits_type::eof())
        return;
    while(!in.eof()) {
        //if (in.peek() == std::ifstream::traits_type::eof())
        //    return;
        Jucator jucator;
        in >> jucator;
        Repository::store(jucator);
    }
}

bool Repository::exista(Jucator& jucator) {
    auto index = std::find_if(this->storage.begin(), this->storage.end(), [&jucator](Jucator& alt_jucator){
        return jucator == alt_jucator;
    });
    if (index == storage.end())
        return false;
    return true;
}

void Repository::store(Jucator &jucator) {
    if (!exista(jucator)) {
        storage.push_back(jucator);
    }
}

vector <Jucator> Repository::get_all() const {
    return this->storage;
}

void Repository::update_puncte(const string &nume, int puncte){
    auto index = std::find_if(storage.begin(), storage.end(), [&nume](Jucator &jucator){
        return nume == jucator.get_nume();
    });
    int puncte_vechi = (*index).get_puncte(), puncte_noi = puncte_vechi + puncte;
    (*index).set_puncte(puncte_noi);
};

void Repository::recalc_ranking() {
    sort(storage.begin(), storage.end(), [](Jucator &j1, Jucator &j2){
        return j1.get_puncte() > j2.get_puncte();
    });
    int rank = 1;
    for (auto & j: storage) {
        j.set_ranking(rank);
        ++rank;
    }
}
void Repository::elimina(int m) {
    vector <Jucator> schimb;
    int rank_acc = this->storage.size() - m;
    for (auto const& j: this->storage) {
        if (j.get_rank() <= rank_acc)
            schimb.push_back(j);
    }
    this->storage.clear();
    this->storage = schimb;
}
void test_repo() {
    Repository repo{"inexistent.txt"};
    Repository repo1{"gol.txt"};
    Repository repo_bun{"test.txt"};
    auto all = repo_bun.get_all();
    assert(all.size() == 2);
    assert(all[0].get_nume() == "Paul Colta");
    assert(all[0].get_tara() == "Romania");
    assert(all[0].get_puncte() == 3432);
    assert(all[0].get_rank() == 2);
    assert(all[1].get_nume() == "Marian Doina");
    assert(all[1].get_tara() == "Moldova");
    assert(all[1].get_puncte() == 3821);
    assert(all[1].get_rank() == 1);
    Jucator j1{"Paul", "romania", 234, 2};
    assert(repo_bun.exista(j1) == false);
    assert(repo_bun.exista(all[0]));
}