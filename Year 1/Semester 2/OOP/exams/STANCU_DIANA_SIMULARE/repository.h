//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef STANCU_DIANA_SIMULARE_REPOSITORY_H
#define STANCU_DIANA_SIMULARE_REPOSITORY_H
#include "domain.h"
#include <vector>
#include <fstream>
using std::vector;
using std::ifstream;
class Repository {
private:
    string filename;
    vector <Elev> storage;
    void load_data();
public:
    //constructori
    Repository(const string& filename) : filename {filename} {
        load_data();
    };
    /*
     * functie care adauga elev in repo
     *
     * @param: Elev elev
     * @return: -
     */
    void store(Elev& elev);
    /*
     * functie care sterge elev din repo
     *
     * @param: Elev elev
     * @return: -
     */
    void erase(Elev& elev);
    /*
     * functie care returneaza un vector cu elevi
     *
     * @param: -
     * @return: vector <Elev>
     */
    vector <Elev> get_all() const;
};

void test_repository();

#endif //STANCU_DIANA_SIMULARE_REPOSITORY_H
