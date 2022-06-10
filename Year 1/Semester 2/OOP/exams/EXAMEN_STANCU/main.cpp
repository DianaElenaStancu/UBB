#include "ui.h"
#include "inProgressW.h"
#include "openW.h"
#include "closeW.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    test_domain();
    test_repo();
    test_service();
    std::cout << "Tests passed\n";

    string filename = "date.txt";
    Repo repo(filename);
    Service srv(repo);
    Ui ui(srv);
    ui.show();
    CloseW f1(srv);
    f1.show();
    inProgressW f2(srv);
    f2.show();
    openW f3(srv);
    f3.show();

    return QApplication::exec();
}
