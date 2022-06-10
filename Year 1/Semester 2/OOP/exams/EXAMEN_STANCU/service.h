//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#ifndef EXAMEN_STANCU_SERVICE_H
#define EXAMEN_STANCU_SERVICE_H
#include "repository.h"
#include <algorithm>
#include "observer.h"

class Service : public Observable{
private:
    Repo &repo;
public:
    Service(Repo &repo) : repo { repo } , Observable(){};
    /*
     * sorteaza toate elementele
     * return: vector cu el de tip Task
     */
    vector <Task> getAll();
    /*
     * filtreaza toate elementele
     * param: string s
     * return: vectorul cu taskurile a caror programatori (cel putin unul) are in componenta stringul s
     */
    vector <Task> filter(string s);
    /*
     * returneaza taskurile cu statusul open
     */
    vector <Task>  opent();
    /*
 * returneaza taskurile cu statusul closed
 */
    vector <Task>  closedt();
    /*
 * returneaza taskurile cu statusul inprogress
 */
    vector <Task>  inprogresst();
    /*
     * adauga un element in repo
     * param: int id,
     *          string descriere,
     *          string stare,
     *          vector progr cu el de tip str
     * return: -
     */
    void store(int id, string descriere, string stare, vector <string> progr);
    /*
    * modifica starea unui task
    * param: Task, string s
    */
    void change_stare(Task task, string s);

};

void test_service();
#endif //EXAMEN_STANCU_SERVICE_H
