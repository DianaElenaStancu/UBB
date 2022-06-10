//
// Created by Diana-Elena Stancu on 10/06/2022.
//

#ifndef EXAMEN_STANCU_OBSERVER_H
#define EXAMEN_STANCU_OBSERVER_H
#include <vector>
using std::vector;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer(){};
};

class Observable {
private:
    vector <Observer*> observers;
public:
    void addObserver(Observer *obs);
    void removeObserver(Observer *obs);
    void notify() const;
};


#endif //EXAMEN_STANCU_OBSERVER_H
