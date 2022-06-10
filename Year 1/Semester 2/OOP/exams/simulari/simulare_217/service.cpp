//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "service.h"

vector <Device> Service::get_all() const {
    return this->repo.get_all();
}

vector <Device> Service::sort_model() const{
    auto all = repo.get_all();
    std::sort(all.begin(), all.end(), [](Device &d1, Device &d2){
        return d1.get_model() < d2.get_model();
    });
    return all;
}

vector <Device> Service::sort_an() const{
    auto all = repo.get_all();
    std::sort(all.begin(), all.end(), [](Device &d1, Device &d2){
        return d1.get_an() < d2.get_an();
    });
    return all;
}