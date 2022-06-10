//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#ifndef PRACTICEOOP_TEST_REPO_H
#define PRACTICEOOP_TEST_REPO_H
#include "repository.h"
#include <sstream>
using std::stringstream;
class test_repo {
private:
    void test_store() const;
    void test_erase() const;
    void test_modify() const;
    void test_find() const;
    void test_print() const;
public:
    void run_all() const;
};


#endif //PRACTICEOOP_TEST_REPO_H
