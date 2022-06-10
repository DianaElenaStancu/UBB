//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "domain.h"
string Jucator::get_nume() const{
    return this->nume;
}
string Jucator::get_tara() const{
    return this->tara;
}
int Jucator::get_puncte() const{
    return this->puncte;
}
int Jucator::get_rank() const{
    return this->rank;
}
void Jucator::set_puncte(const int puncte_noi){
    this->puncte = puncte_noi;
}
void Jucator::set_ranking(const int rank_nou){
    this->rank = rank_nou;
}
bool Jucator::operator==(Jucator& jucator){
    return jucator.nume == this->nume;
}
istream& operator >>(istream& in, Jucator& jucator){
    string line, del = ",";
    getline(in, line);
    jucator.nume = line.substr(0, line.find(del));
    line.erase(0, line.find(del) + 2);
    jucator.tara = line.substr(0, line.find(del));
    line.erase(0, line.find(del) + 2);
    jucator.puncte = stoi(line.substr(0, line.find(del)));
    line.erase(0, line.find(del) + 2);
    jucator.rank = stoi(line.substr(0, line.find(del)));
    return in;
}
ostream& operator <<(ostream& out, const Jucator& jucator){
    out << jucator.nume << ", " << jucator.tara << ", " << jucator.puncte << ", " << jucator.rank << "\n";
    return out;
}

string Jucator::to_string() const{
    return nume + ", " + tara + ", " + std::to_string(puncte) + ", " + std::to_string(rank) + "\n";
}

void test_domain(){
    Jucator j2, j3; Jucator j1{"Paul", "romania", 234, 2};
    assert(j1.get_nume() == "Paul");
    assert(j1.get_puncte() == 234);
    assert(j1.get_rank() == 2);
    assert(j1.get_tara() == "romania");
    std::strstream sout;
    sout << j2;
    sout >> j3;
    assert(j2 == j3);
    j1.set_puncte(20);
    j1.set_ranking(1);
    assert(j1.to_string() == "Paul, romania, 20, 1\n");
}