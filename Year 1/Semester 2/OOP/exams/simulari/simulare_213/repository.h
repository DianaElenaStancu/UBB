//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef SIMULARE_213_REPOSITORY_H
#define SIMULARE_213_REPOSITORY_H
#include "domain.h"
#include <vector>
#include <fstream>
#include <exception>
using std::ifstream;
using std::ofstream;
class Repository {
private:
    string filename;
    std::vector <Apartament> storage;
    void load_from_file();
    bool exista(const Apartament& apartament);
public:
    Repository(const string& filename) : filename {filename}{
        this->load_from_file();
    };
    void store(const Apartament& apartament);
    void remove(const Apartament& apartament);
    std::vector <Apartament> get_all() const;
    ~Repository() = default;
};


#endif //SIMULARE_213_REPOSITORY_H
