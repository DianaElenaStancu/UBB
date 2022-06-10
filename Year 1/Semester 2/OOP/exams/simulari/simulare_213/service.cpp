//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#include "service.h"

std::vector <Apartament> Service::get_all() const {
    return this->repo.get_all();
}

void Service::remove(Apartament apartament) {
    std::cout << apartament.to_string() << std::endl;
    this->repo.remove(apartament);
}

std::vector <Apartament> Service::filter_pret(double pret1, double pret2) {
    auto all = this->repo.get_all();
    std::vector <Apartament> filtered;
    std::copy_if(all.begin(), all.end(), std::back_inserter(filtered), [&](const Apartament& a){
        return a.get_pret() >= pret1 && a.get_pret() <= pret2;
    });
    return filtered;
}

std::vector <Apartament> Service::filter_suprafata(int sup1, int sup2) {
    auto all = this->repo.get_all();
    std::vector <Apartament> filtered;
    std::copy_if(all.begin(), all.end(), std::back_inserter(filtered), [&](const Apartament& a){
        return a.get_suprafata() >= sup1 && a.get_suprafata() <= sup2;
    });
    return filtered;
}

std::vector <Apartament> Service::filter_tip_suprafata(double pret1, double pret2, int sup1, int sup2) {
    auto all = this->repo.get_all();
    std::vector <Apartament> filtered;
    std::copy_if(all.begin(), all.end(), std::back_inserter(filtered), [&](const Apartament& a){
        return a.get_pret() >= pret1 && a.get_pret() <= pret2 && a.get_suprafata() >= sup1 && a.get_suprafata() <= sup2;
    });
    return filtered;
}