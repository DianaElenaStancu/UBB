//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_212_REPOSITORY_H
#define SIMULARE_212_REPOSITORY_H
#include "domain.h"
#include <fstream>
#include <vector>
using std::vector;
using std::istream;
using std::ofstream;
class RepoProc {
private:
    vector <Procesor> storage;
    string filename;
    void load_data();
public:
    RepoProc(const string& filename) : filename { filename } {
        load_data();
    };
    void store(Procesor &proc);
    vector <Procesor> get_all() const;
};

class RepoPlaci {
private:
    vector <PlacaDeBaza> storage;
    string filename;
    void load_data();
    void write_to_file();
    bool exista(const PlacaDeBaza &placa) const;
public:
    RepoPlaci(const string& filename) : filename { filename } {
        load_data();
    };
    void store(PlacaDeBaza &placa);
    vector <PlacaDeBaza> get_all() const;
};


#endif //SIMULARE_212_REPOSITORY_H
