#include <QApplication>
#include "tests.h"
#include "ui.h"
#include "gui.h"

int main(int argc, char *argv[]) {

    TestAll();
    cout << "Tests passed!\n";
    Repository repository{};
    Service service{repository};
    //ConsoleUI console{service};
    //console.run();

    QApplication a(argc, argv);
    GUI gui(service);
    gui.show();
   /* QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();*/
    return QApplication::exec();
}
