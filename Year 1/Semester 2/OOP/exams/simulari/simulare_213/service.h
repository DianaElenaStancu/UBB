//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef SIMULARE_213_SERVICE_H
#define SIMULARE_213_SERVICE_H
#include "repository.h"

class Service {
private:
    Repository &repo;
public:
    Service(Repository &repo) : repo { repo } {};
    std::vector <Apartament> get_all() const;
    void remove(Apartament apartament);
    std::vector <Apartament> filter_pret(double pret1, double pret2);
    std::vector <Apartament> filter_suprafata(int sup1, int sup2);
    std::vector <Apartament> filter_tip_suprafata(double pret1, double pret2, int sup1, int sup2);
};


#endif //SIMULARE_213_SERVICE_H
