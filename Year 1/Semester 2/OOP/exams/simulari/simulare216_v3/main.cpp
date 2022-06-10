#include "gui.h"
#include <iostream>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //tests
    test_domain();
    //test_repo();
    std::cout << "Tests passed\n";

    //run
    Repository repo{"jucatori.txt"};
    Service srv{repo};
    Gui gui{srv};
    gui.show();
    return QApplication::exec();
}
