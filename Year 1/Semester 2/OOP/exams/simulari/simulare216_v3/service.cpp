//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "service.h"

vector <Jucator> Service::get_all() const{
    return this->repo.get_all();
}
bool Service::exista_nume(const string& nume) const {
   auto all = this->repo.get_all();
   auto index = std::find_if(all.begin(), all.end(), [&nume](Jucator &jucator){
       return nume == jucator.get_nume();
   });
   if (index == all.end())
       return false;
   return true;
}

void Service::update_puncte(const string &nume, int puncte, const int metoda) {
    if (metoda == 1) { //semifinala
        puncte = (puncte*75)/100;
    } else if (metoda == 2){ //sferturi
        puncte = puncte/2;
    }
    this->repo.update_puncte(nume, puncte);
}
void Service::elimina(int m) {
    this->repo.elimina(m);
}
void Service::recalc_ranking() {
    this->repo.recalc_ranking();
}

void Service::adauga(const string& nume, const string& tara, const int rank){
    auto all = this->repo.get_all();
    std::sort(all.begin(), all.end(), [&](Jucator &j1, Jucator &j2){
        return j1.get_rank() < j2.get_rank();
    });
    int size = all.size();
    int upper, lower;
    if (all[0].get_rank() > rank) {
        lower = all[0].get_puncte();
        upper = 5000;
    } else if (all[size - 1].get_rank() < rank) {
        upper = all[size - 1].get_puncte();
        lower = 0;
    } else {
        for (int i = 0; i < size - 1; i++) {
            if (rank > all[i].get_rank() && rank < all[i + 1].get_rank()) {
                upper = all[i].get_puncte();
                lower = all[i + 1].get_puncte();
                break;
            }
        }
    }
    int puncte = rand()%(upper - lower + 1) + lower;
    Jucator jucator {nume, tara, puncte, rank};
    this->repo.store(jucator);
}