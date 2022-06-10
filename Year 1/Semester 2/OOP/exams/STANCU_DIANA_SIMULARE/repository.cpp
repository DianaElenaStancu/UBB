//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "repository.h"


void Repository::load_data(){
    ifstream in(this->filename, std::ios::in);
    if(!in.is_open())
        return;
    if(in.peek() == ifstream::traits_type::eof())
        return;
    while(!in.eof()) {
        Elev elev;
        in >> elev;
        Repository::store(elev);
    }
}

void Repository::store(Elev& elev){
    storage.push_back(elev);
}
void Repository::erase(Elev& elev){
    auto index = std::find_if(storage.begin(), storage.end(), [&elev](Elev &e){
        return elev == e;
    });
    if(index != storage.end())
        storage.erase(index);
}
vector <Elev> Repository::get_all() const{
    return this->storage;
}


void test_repository(){
    Repository repo{"inex.txt"};
    assert(repo.get_all().size() == 0);
    Repository repo1{"gol.txt"};
    assert(repo1.get_all().size() == 0);
    Repository repo2{"test.txt"};
    assert(repo2.get_all().size() == 2);
    Elev elev{"06660","Nume1","Prenume1",9,10};
    repo2.erase(elev);
    assert(repo2.get_all().size() == 1);
}