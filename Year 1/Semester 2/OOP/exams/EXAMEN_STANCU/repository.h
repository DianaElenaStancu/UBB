//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#ifndef EXAMEN_STANCU_REPOSITORY_H
#define EXAMEN_STANCU_REPOSITORY_H
#include "domain.h"
#include <vector>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::vector;
class Repo {
private:
    vector <Task> storage;
    string filename;
    void read_from_file();
    void write_to_file();

public:
    Repo(string& filename) : filename { filename } {
        read_from_file();
    };

    /*
     * sorteaza taskurile
     * return: -
     *          se modifica vectorul storage
     */
    void sort() ;

    /*
     * verifica daca exista un element in storage
     * param: Task
     * return: 0 , daca nu exista, 1 in caz contrar
     */
    int exista(Task &cautat);

    /*
     * adauga un element in storage
     * param: Task
     */
    void store(Task &task);

    /*
     * modifica starea unui task
     * param: Task, string s
     */
    void change_stare(Task &task, string s);

    /*
     * returneaza toate elementele din storage
     */
    vector <Task> getAll();

};

void test_repo();

#endif //EXAMEN_STANCU_REPOSITORY_H
