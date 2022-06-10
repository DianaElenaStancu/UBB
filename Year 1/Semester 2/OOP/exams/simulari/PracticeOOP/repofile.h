//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef PRACTICEOOP_REPOFILE_H
#define PRACTICEOOP_REPOFILE_H
#include "repository.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
class Repofile : public Repository{
private:
    string filename;
    void loadFromFile();
    void writeToFile();
public:
    Repofile(const string& filename) : Repository(), filename { filename } {
        this->loadFromFile();
    };
    void store(const Masina& masina) override;
    void erase(const Masina& masina) override;
    void modify(const Masina& masinaModify) override;
};


#endif //PRACTICEOOP_REPOFILE_H
