//
// Created by Diana-Elena Stancu on 24/05/2022.
//

#include "Observer.h"

void Observable::addObserver(Observer* obs) {
    this->observers.push_back(obs);
}

void Observable::removeObserver(Observer* obs) {
    this->observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Observable::notify() const {
    //for (const auto& obs : observers) {
    //	obs->update();
    //}
    std::for_each(observers.begin(), observers.end(), [](Observer* obs) {
        obs->update();
    });
}