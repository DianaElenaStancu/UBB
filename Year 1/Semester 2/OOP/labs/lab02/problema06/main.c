//
// Created by Diana-Elena Stancu on 05/03/2022.
//

#include "main.h"
#include "ui.h"
#include "repo.h"
#include "service.h"

#include "tests.h"
#include <stdio.h>

int main(){
    testAll();
    printf("Tests passed!\n");//run with coverage

//    MateriiRepo repo = createRepo();
//    Service srv = createService(repo);
//    Ui ui = createUi(srv);
//    run(ui);

    printf("Bye bye!");
    return 0;
}