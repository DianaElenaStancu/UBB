//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "service.h"


vector <Elev> Service::get_all() const{
    return this->repo.get_all();
}

vector <Elev> Service::sort_medie() const{
    auto res = this->repo.get_all();
    sort(res.begin(), res.end(), [](Elev &e1, Elev &e2){
        return e1.get_medie() > e2.get_medie();
    });
    return res;
}

vector <Elev> Service::sort_clasa() const{
    auto res = this->repo.get_all();
    sort(res.begin(), res.end(), [](Elev &e1, Elev &e2){
        return e1.get_clasa() < e2.get_clasa();
    });
    return res;
}

vector <Elev> Service::sort_nume() const{
    auto res = this->repo.get_all();
    sort(res.begin(), res.end(), [](Elev &e1, Elev &e2){
        return e1.get_nume() < e2.get_nume();
    });
    return res;
}

void Service::erase(Elev &elev){
    this->repo.erase(elev);
}

void test_service(){

    Elev e {"06660","Nume1","Prenume1",9,10};
    Elev ee {"03214","Nume2","Prenume2",10,9.3};

    Repository repo{"test.txt"};
    Service srv(repo);
    assert(srv.get_all().size() == 2);
    auto all1 = srv.sort_clasa();
    assert(all1[0] == e);
    assert(all1[1] == ee);
    auto all2 = srv.sort_medie();
    assert(all2[0] == e);
    assert(all2[1] == ee);
    auto all3 = srv.sort_nume();
    assert(all3[0] == e);
    assert(all3[1] == ee);
    srv.erase(e);
    assert(srv.get_all().size() == 1);
}