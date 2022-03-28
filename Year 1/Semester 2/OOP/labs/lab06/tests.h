//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#ifndef LAB06_TESTS_H
#define LAB06_TESTS_H

#include <cassert>
#include "domain.h"

class Test {
protected:
    virtual void ctors(){}
    virtual void getters(){}
    virtual void setters(){}
    virtual void operators(){}
public:
    void run() {
        ctors();
        getters();
        setters();
        operators();
    }
    Test() = default;
};

void TestAll();

#endif //LAB06_TESTS_H
