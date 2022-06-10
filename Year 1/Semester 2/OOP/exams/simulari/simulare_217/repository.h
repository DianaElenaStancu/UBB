//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#ifndef SIMULARE_217_REPOSITORY_H
#define SIMULARE_217_REPOSITORY_H
#include "domain.h"
#include <vector>
#include <fstream>
using std::vector;
using std::ifstream;
class Repository {
private:
    vector <Device> storage;
    string filename;
    void load_data();
public:
    Repository(const string& filename) : filename { filename } {
        load_data();
    };
    void store(Device &device);
    vector <Device> get_all() const;
};


#endif //SIMULARE_217_REPOSITORY_H
