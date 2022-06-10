//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#include "domain.h"

int Task::get_id() { return id; }
string Task::get_descriere() {return descriere;}
string Task::get_stare() {return stare;}
vector <string> Task::get_programatori() {return programatori;}

istream& operator >>(istream &in, Task &task) {
    string line, sep = ";", v = ",";
    getline(in, line);
    task.id = stoi(line.substr(0, line.find(sep)));
    line.erase(0, line.find(sep) + 1);
    task.descriere =line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    string pr =line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    while(pr.find(v) != string::npos) {
        string p = pr.substr(0, pr.find(v));
        pr.erase(0, pr.find(v) + 1);
        // cout << p << endl;
        task.programatori.push_back(p);
    }
    task.programatori.push_back(pr);
    task.stare = line.substr(0, line.find(sep));
    line.erase(0, line.find(sep) + 1);
    return in;
}

ostream& operator <<(ostream& out, Task &task) {
    string rez = "";
    rez += std::to_string(task.id) + ";" + task.descriere + ";";
    for (auto &nume: task.programatori)
        rez += nume+",";
    rez.pop_back();
    rez += ";" + task.stare + "\n";
    out << rez;
    return out;
}



void Task::set_stare(string stare_noua) {
    this->stare = stare_noua;
}


void test_domain() {

    Task t1, t2(1, "a", {"ana", "maria"}, "open");
    std::strstream sout;
    sout << t2;
    sout >> t1;
    assert(t1.get_id() == 1);
    assert(t1.get_descriere() == "a");
    assert(t1.get_programatori().size() == 2);
    assert(t1.get_stare() == "open");
    t1.set_stare("closed");
}