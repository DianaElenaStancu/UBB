//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "service.h"

const vector <PlacaDeBaza> Service::get_placi() const {
    return this->repo_placi.get_all();
}

const vector <Procesor> Service::get_proc() const {
    return this->repo_proc.get_all();
}

void Service::add_placa(const string& nume, const string& soclu, const double pret){
    PlacaDeBaza placa{nume, soclu, pret};
    if (this->val.validate_placa(placa)) {
        this->repo_placi.store(placa);
    }
}

vector <PlacaDeBaza> Service::filter_placi(const string &soclu) const{
    vector <PlacaDeBaza> res;
    auto all = this->get_placi();
    std::copy_if(all.begin(), all.end(), std::back_inserter(res), [&soclu](PlacaDeBaza& p){
        return soclu == p.get_soclu();
    });
    return res;
}
