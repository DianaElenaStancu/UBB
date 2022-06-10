#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo{"data.txt"};
    Service srv{repo};
    Gui gui{srv};
    gui.show();
    return QApplication::exec();
}
