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
    Repository repository{};
    //RepositoryProb repositoryprob{0.50};
    Service service{repository};
    ConsoleUI console{service};
    console.run();

    return 0;
}



