//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#include "service.h"


vector <Task> Service::getAll(){
    return repo.getAll();
}

void Service::store(int id, string descriere, string stare, vector <string> progr) {
    Task t{id, descriere, progr, stare};
    repo.store(t);
    notify();
}

vector <Task> Service::filter(string s){
    auto all = repo.getAll();
    vector <Task> rez;
    for (auto e: all) {
        for(auto p: e.get_programatori())
            if (p.find(s) != string::npos) {
                rez.push_back(e);
                break;
            }
    }
    return rez;
}

void Service::change_stare(Task task, string s) {
    repo.change_stare(task, s);
    notify();
}

vector <Task>  Service::opent(){
    vector <Task> lista;
    auto all = repo.getAll();
    std::copy_if(all.begin(), all.end(), back_inserter(lista), [](Task t){
        return t.get_stare() == "open";
    });
    return lista;
}
vector <Task>  Service::closedt(){
    vector <Task> lista;
    auto all = repo.getAll();
    std::copy_if(all.begin(), all.end(), back_inserter(lista), [](Task t){
        return t.get_stare() == "closed";
    });
    return lista;
}
vector <Task>  Service::inprogresst(){
    vector <Task> lista;
    auto all = repo.getAll();
    std::copy_if(all.begin(), all.end(), back_inserter(lista), [](Task t){
        return t.get_stare() == "inprogress";
    });
    return lista;
}

void test_service(){
    string f = "test_date.txt";
    Repo repo{f};
    Service srv{repo};
    assert(srv.inprogresst().size() == 2);
    assert(srv.closedt().size() == 1);
    assert(srv.opent().size() == 0);
    Task t2 {100, "d", {"a"}, "open"};
    srv.change_stare(t2, "open");
}