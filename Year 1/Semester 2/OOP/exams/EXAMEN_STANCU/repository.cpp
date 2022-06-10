//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#include "repository.h"


void Repo::read_from_file() {
    ifstream in(filename, std::ios::in);
    if (!in.is_open())
        return;
    while(!in.eof()) {
        if (in.peek() == std::ifstream::traits_type::eof()) {
            return;
        }
        Task t;
        in >> t;
        storage.push_back(t);
    }
}

void Repo::write_to_file() {
    ofstream out(filename, std::ios::trunc);
    if(!out.is_open())
        return;
    for (auto e: storage)
        out << e;
}

void Repo::sort() {
    std::sort(this->storage.begin(), this->storage.end(), [](Task t1, Task t2){
        return t1.get_stare() < t2.get_stare();
    });
}

int Repo::exista(Task &cautat){
    auto it = find_if(storage.begin(), storage.end(), [&](Task t){
        return t.get_id() == cautat.get_id();
    });
    return it != storage.end();
}

void Repo::store(Task &task) {
    if(!exista(task)) {
        storage.push_back(task);
        sort();
        write_to_file();
    } else
        throw 1;
}

vector <Task> Repo::getAll() {
    sort();
    return storage;
}

void Repo::change_stare(Task &task, string s) {
    for (auto &e : storage) {
        if (e.get_id() == task.get_id()) {
            e.set_stare(s);
            break;
        }
    }
    sort();
    write_to_file();
}

void test_repo(){
    string f = "inexistent.txt";
    Repo repo{f};
    assert(repo.getAll().size()== 0);
    f = "test_date.txt";
    Repo repo1{f};
    //std::cout << repo.getAll().size();
    assert(repo1.getAll().size() == 3);

    Task t1 {3, "d", {"a"}, "open"};
    try{
        //repo1.store(t1);
        //assert(false);
    } catch(...) {

    }
    Task t2 {100, "d", {"a"}, "open"};
    //repo1.store(t2);
    repo1.change_stare(t2, "closed");
}