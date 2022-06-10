#include "gui.h"
#include <iostream>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    test_domain();
    std::cout << "tests passed :)\n";
    RepoProc repoproc("proc.txt");
    RepoPlaci repoplaci("placi.txt");
    Validator val{};
    Service srv(repoproc, repoplaci, val);
    Gui gui(srv);
    gui.show();
    return QApplication::exec();
}
