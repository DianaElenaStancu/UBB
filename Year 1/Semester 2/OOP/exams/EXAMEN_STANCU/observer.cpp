//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#include "observer.h"
#include <iostream>
using namespace std;
void Observable::addObserver(Observer *obs) {
    observers.push_back(obs);
}
void Observable::removeObserver(Observer *obs) {
    observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
}
void Observable::notify() const {
    std::for_each(observers.begin(), observers.end(), [](Observer *obs){
        obs->update();
    });
}