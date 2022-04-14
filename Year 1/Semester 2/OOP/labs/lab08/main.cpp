//
// Created by Diana-Elena Stancu on 06/04/2022.
//
#include <iostream>
#include "tests.h"
#include "ui.h"
using namespace std;
int main() {
    TestAll();
    cout << "Tests passed!\n";
    Repository repo{};
    Service service{repo};
    ConsoleUI console{service};
    console.run();
    return 0;
}



