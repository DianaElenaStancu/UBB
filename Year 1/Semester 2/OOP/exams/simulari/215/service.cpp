//
// Created by Diana-Elena Stancu on 19/05/2022.
//

#include "service.h"

vector <Joc> Service::get_all() const{
    return this->repo.get_all();
}