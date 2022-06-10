#include "gui.h"
#include <iostream>
int main(int argc, char *argv[]) {
    test_domain();
    test_repository();
    test_service();
    std::cout << "Tests passed";

    QApplication a(argc, argv);
    Repository repo{"elevi.txt"};
    Service srv{repo};
    Gui gui{srv};
    gui.show();
    return QApplication::exec();
}
