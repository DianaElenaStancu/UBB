//
// Created by Diana-Elena Stancu on 27/03/2022.
//
#include <iostream>
#include "tests.h"
#include "ui.h"
using namespace std;
int main() {
    TestAll();
    cout << "Tests passed!\n";
    ConsoleUI console;
    console.run();
    return 0;
}



