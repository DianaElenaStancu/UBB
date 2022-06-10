//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#ifndef EXAMEN_STANCU_DOMAIN_H
#define EXAMEN_STANCU_DOMAIN_H
#include <string>
#include <vector>
#include <sstream>
#include <strstream>
#include <iostream>
using std::istream;
using std::ostream;
using std::string;
using std::vector;
class Task {
private:
    string descriere;
    int id;
    vector<string> programatori;
    string stare;
public:
    Task() = default;

    Task(int id, string descriere, vector<string> programatori, string stare) : id{id}, descriere{descriere},
                                                                                programatori{programatori},
                                                                                stare{stare} {};
    //gettere
    int get_id();

    string get_descriere();

    string get_stare();

    vector<string> get_programatori();

    //scrierea si afisarea unui obiect de tip Task
    friend ostream &operator<<(ostream &out, Task &task);

    friend istream &operator>>(istream &in, Task &task);

    //setter
    void set_stare(string stare_noua);

};
void test_domain();

#endif //EXAMEN_STANCU_DOMAIN_H
