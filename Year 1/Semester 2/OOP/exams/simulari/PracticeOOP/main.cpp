#include "gui.h"
#include "test_domain.h"
#include "test_repo.h"
#include "test_validator.h"
#include "test_service.h"
#include "gui.h"
#include "test_repofile.h"
#include "GuiFilter.h"
#include <iostream>
using std::cout;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    test_domain testDomain;
    testDomain.run_all();
    test_repo testRepo;
    testRepo.run_all();
    test_validator testValidator;
    testValidator.run_all();
    test_service testService;
    testService.run_all();
    test_repofile testRepofile;
    testRepofile.run_all();
    cout << "Tests passed :)\n";
    Repository repo;
    Validator val;
    Service service{repo, val};

    Gui gui{service};
    gui.show();

    GuiFilter guifilter{service};
    guifilter.show();



    return QApplication::exec();
}
