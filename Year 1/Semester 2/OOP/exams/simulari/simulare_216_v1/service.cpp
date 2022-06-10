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