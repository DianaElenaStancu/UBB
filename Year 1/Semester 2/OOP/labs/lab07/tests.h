//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#ifndef LAB06_TESTS_H
#define LAB06_TESTS_H

#include <cassert>
#include <cstring>
#include <strstream>
#include "domain.h"
#include "dynamic_array.h"
//#include "repository.h"
//#include "exceptions.h"
//#include "validator.h"
#include "service.h"
class Test {
protected:
    virtual void ctors(){} //il declar intr-o clasa si il redefinesc intr-o clasa derivata
    virtual void getters(){}
    virtual void setters(){}
    virtual void operators(){}
    virtual void add(){}
    virtual void find(){}
    virtual void remove(){}
    virtual void modify(){}
    virtual void sort(){}
    virtual void filter(){}
    virtual void methods(){}
    virtual void dynamic_array(){}
    virtual void iterator(){}
public:
    void run() {
        ctors();
        getters();
        setters();
        operators();
        add();
        find();
        remove();
        sort();
        modify();
        filter();
        methods();
        dynamic_array();
        iterator();
    }
    Test() = default;
};

void TestAll();

#endif //LAB06_TESTS_H