//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef INC_215_REPOSITORY_H
#define INC_215_REPOSITORY_H

#include "domain.h"
#include <vector>
#include <fstream>
using std::vector;
using std::ifstream;

class RepositoryABS {
private:
    string filename;
    vector <Joc> storage;
public:
    virtual void load_data() = 0;
    RepositoryABS() = default;
   /* explicit RepositoryABS( const string& filename ) : filename {filename } {
        load_data();
    };*/

    virtual void store(const Joc& joc) = 0;
    virtual vector <Joc> get_all() const = 0;
};

class Repository : public RepositoryABS{
private:
    string filename;
    vector <Joc> storage;
public:
    virtual void load_data() override;
    Repository(const string& filename) : filename {filename } {
        load_data();
    };
    virtual void store(const Joc& joc) override;
    virtual vector <Joc> get_all() const override;
};

void test_repository();
#endif //INC_215_REPOSITORY_H
