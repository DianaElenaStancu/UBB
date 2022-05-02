//
// Created by Diana-Elena Stancu on 20/04/2022.
//

#ifndef LAB07_REPOSITORYFILE_H
#define LAB07_REPOSITORYFILE_H
#include "repository.h"
#include <map>
#include <random>
#include <chrono>
#include <fstream>
using std::string;
using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

class RepositoryProb : public Repository {
    double prob;
    int index = 0;
    map <int, Activitate> storage;
    double gen() const;

public:
    RepositoryProb(const double& prob) : Repository(), prob {prob} {
    };

     void add(const Activitate&) override;
     void remove(const Activitate&) override;
     void modify(Activitate& activitate, Activitate& activitate_noua) override;
};


#endif //LAB07_REPOSITORYFILE_H
