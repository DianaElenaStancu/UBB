//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#ifndef STANCU_DIANA_SIMULARE_SERVICE_H
#define STANCU_DIANA_SIMULARE_SERVICE_H
#include "repository.h"

class Service {
private:
    Repository &repo;
public:
    //constructor
    Service(Repository &repo) : repo {repo} {};
    /*
     * functie care sterge elev din lista
     * @param: Elev elev
     * @return:-
     */
    void erase(Elev &elev);
    /*
    * functie care returneaza elementele din lista
    * @param: -
    * @return: vector <Elev>
    */
    vector <Elev> get_all() const;
    /*
    * functie care sorteaza elementele din lista
    * @param: -
    * @return: vector <Elev> cu elementele sortate dupa medie
    */
    vector <Elev> sort_medie() const;
    /*
    * functie care sorteaza elementele din lista
    * @param: -
    * @return: vector <Elev> cu elementele sortate dupa clasa
    */
    vector <Elev> sort_clasa() const;
    /*
    *  functie care sorteaza elementele din lista
    * @param: -
    * @return: vector <Elev> cu elementele sortate dupa nume
    */
    vector <Elev> sort_nume() const;
};

void test_service();

#endif //STANCU_DIANA_SIMULARE_SERVICE_H
