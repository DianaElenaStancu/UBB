//
// Created by Diana-Elena Stancu on 15/05/2022.
//

#ifndef PRACTICEOOP_TEST_DOMAIN_H
#define PRACTICEOOP_TEST_DOMAIN_H
#include "domain.h"
#include <sstream>
#include <fstream>
#include <iostream>
using std::stringstream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

class test_domain {
private:
    void test_get_set() const;
    void test_copy() const;
    void test_compare() const;
    void test_print() const;
    void testIO() const;
public:
    void run_all() const;
};


#endif //PRACTICEOOP_TEST_DOMAIN_H
