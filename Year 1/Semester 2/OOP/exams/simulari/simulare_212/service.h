//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_212_SERVICE_H
#define SIMULARE_212_SERVICE_H
#include "repository.h"
#include "validator.h"
#include <iostream>
class Service {
private:
    RepoProc& repo_proc;
    RepoPlaci& repo_placi;
    Validator& val;
public:
    Service(RepoProc& repo_proc, RepoPlaci& repo_placi, Validator &val) : repo_placi{ repo_placi }, repo_proc {repo_proc}, val { val } {};
    const vector <PlacaDeBaza> get_placi() const;
    const vector <Procesor> get_proc() const;
    void add_placa(const string& nume, const string& soclu, const double pret);
    vector <PlacaDeBaza> filter_placi(const string &soclu) const;
};


#endif //SIMULARE_212_SERVICE_H
