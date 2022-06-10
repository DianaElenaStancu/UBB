//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_216_V1_SERVICE_H
#define SIMULARE_216_V1_SERVICE_H
#include "repository.h"

class Service {
private:
    Repository &repo;
public:
    Service(Repository &repo) : repo { repo } {};
    vector <Jucator> get_all() const;
    bool exista_nume(const string &nume) const;
    void update_puncte(const string &nume, int puncte,const int metoda);
    void recalc_ranking();
    void elimina(int m);
};


#endif //SIMULARE_216_V1_SERVICE_H
