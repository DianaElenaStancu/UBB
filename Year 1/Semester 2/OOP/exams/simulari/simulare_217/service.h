//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_217_SERVICE_H
#define SIMULARE_217_SERVICE_H
#include "repository.h"
#include <algorithm>
class Service {
private:
    Repository &repo;
public:
    Service(Repository &repo) : repo { repo } {};
    vector <Device> get_all() const;
    vector <Device> sort_model() const;
    vector <Device> sort_an() const;
};


#endif //SIMULARE_217_SERVICE_H
