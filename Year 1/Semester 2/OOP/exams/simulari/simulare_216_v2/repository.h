//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_216_V1_REPOSITORY_H
#define SIMULARE_216_V1_REPOSITORY_H
#include "domain.h"
#include <vector>
#include <fstream>
#include <iostream>
using std::ifstream;
using std::vector;
class Repository {
private:
    vector <Jucator> storage;
    string filename;
    void read_from_file();
public:
    Repository(const string& filename) : filename { filename } {
        read_from_file();
    };
    bool exista(Jucator& jucator);
    void store(Jucator& jucator);
    vector <Jucator> get_all() const;
    void update_puncte(const string &nume, int puncte);
    void recalc_ranking();
    void elimina(int m);
};

void test_repo();

#endif //SIMULARE_216_V1_REPOSITORY_H
