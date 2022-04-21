//
// Created by Diana-Elena Stancu on 20/04/2022.
//

#ifndef LAB07_REPOSITORYFILE_H
#define LAB07_REPOSITORYFILE_H
#include "repository.h"
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

class RepositoryFile : public Repository {
    string filename;
    void loadFromFile();
    void writeToFile();
public:
    RepositoryFile(const string& filename) : Repository(), filename {filename} {
      loadFromFile();
    };
    void add(const Activitate&) override;
    void remove(const Activitate&) override;
    void modify(Activitate& activitate, Activitate& activitate_noua) override;
};


#endif //LAB07_REPOSITORYFILE_H
