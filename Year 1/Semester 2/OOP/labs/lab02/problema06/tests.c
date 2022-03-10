//
// Created by Diana-Elena Stancu on 05/03/2022.
//

#include "tests.h"
#include "domain.h"
#include "validator.h"
#include "repo.h"
#include "service.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void testAll() {
    testDomain();
    testValidator();
    testRepo();
    testService();
}

void testDomain() {
    //testing getters and setters
    Materie m1 = createMaterie("lapte", "Napolact", 20);
    Materie m2 = createMaterie("lapte", "Napolact", 20);
    Materie m3 = createMaterie("ciocolata", "Napolact", 20);

    assert(equal(m1, m2) == 1);
    assert(equal(m1, m3) == 0);

    //str function test
    assert(strcmp(str(m1), "nume: lapte; producator: Napolact; cantitate: 20") == 0);


    //copy function
    Materie m4 = copy(m1);
    assert(equal(m1, m4));

    assert(strcmp(getName(&m1), "lapte") == 0);
    assert(strcmp(getProducer(&m1), "Napolact") == 0);
    assert(getQuantity(&m1) == 20);
    setName(&m1, "ciocolata");
    setProducer(&m1, "Milka");
    setQuantity(&m1, 10);
    assert(strcmp(getName(&m1), "ciocolata") == 0);
    assert(strcmp(getProducer(&m1), "Milka") == 0);
    assert(getQuantity(&m1) == 10);
    destroyMaterie(&m1);
    destroyMaterie(&m2);
    destroyMaterie(&m3);
    assert(getName(&m1) == NULL);
    assert(getProducer(&m1) == NULL);
    //?memory leaks check
    //_CrtDumpMemoryLeaks();
}

void testValidator() {
    Materie m1 = createMaterie("lapte", "Napolact", 20);
    assert(validate(&m1));
    Materie m2 = createMaterie("", "Napolact", 20);
    assert(!validate(&m2));
    Materie m3 = createMaterie("lapte", "", 20);
    assert(!validate(&m3));
    Materie m4 = createMaterie("lapte", "Napolact", -10);
    assert(!validate(&m4));
}

void testRepo() {
    MateriiRepo materiiRepo = createRepo();
    assert(getLen(materiiRepo) == 0);
    assert(*materiiRepo.capacity == 100);
    //Materie* repo = getRepo(materiiRepo);
    // verificam daca repo e gol
    Materie m1 = createMaterie("lapte", "Napolact", 20);
    Materie m2 = createMaterie("zahar", "Furnica", 30);
    Materie m3 = createMaterie("ciocolata", "Milka", 10);
    Materie m4 = createMaterie("faina", "Pambac", 2000);
    Materie m5 = createMaterie("lapte", "Zuzu", 3000);


    assert(addMaterie(&materiiRepo, m1));
    assert(getLen(materiiRepo) == 1);
    assert(*materiiRepo.capacity == 100);
    Materie * repo = getRepo(materiiRepo);
    assert(equal(repo[0], m1));
    assert(addMaterie(&materiiRepo, m1) == false);
    setQuantity(&m1, 200);
    assert(addMaterie(&materiiRepo, m1) == false);

    assert(addMaterie(&materiiRepo, m2));
    assert(getLen(materiiRepo) == 2);
    assert(*materiiRepo.capacity == 100);
    repo = getRepo(materiiRepo);
    assert(equal(repo[0], m1));
    assert(equal(repo[1], m2));

    assert(addMaterie(&materiiRepo, m3));
    assert(getLen(materiiRepo) == 3);
    assert(*materiiRepo.capacity == 100);
    repo = getRepo(materiiRepo);
    assert(equal(repo[0], m1));
    assert(equal(repo[1], m2));
    assert(equal(repo[2], m3));

    assert(findMaterie(&materiiRepo, m1) == 0);
    assert(findMaterie(&materiiRepo, m2) == 1);
    assert(findMaterie(&materiiRepo, m3) == 2);
    assert(findMaterie(&materiiRepo, m4) == -1);

    assert(updateMaterie(&materiiRepo, m4) == false);
    assert(updateMaterie(&materiiRepo, m5));
    repo = getRepo(materiiRepo);
    assert(getQuantity(&repo[0]) == 3000);
    assert(strcmp(getProducer(&repo[0]), "Zuzu")==0);

    assert(deleteMaterie(&materiiRepo, m4) == false);
    assert(getLen(materiiRepo) == 3);
    repo = getRepo(materiiRepo);
    assert(equal(repo[0], m1));
    assert(equal(repo[1], m2));
    assert(equal(repo[2], m3));

    assert(deleteMaterie(&materiiRepo, m1));
    assert(getLen(materiiRepo) == 2);
    repo = getRepo(materiiRepo);
    assert(equal(repo[0], m2));
    assert(equal(repo[1], m3));

    assert(deleteMaterie(&materiiRepo, m3));
    assert(getLen(materiiRepo) == 1);
    repo = getRepo(materiiRepo);
    assert(equal(repo[0], m2));

    destroyRepo(&materiiRepo);
}


void testService() {
    MateriiRepo materiiRepo = createRepo();
    Service service = createService(materiiRepo);

    Materie m1 = createMaterie("lapte", "Napolact", 20);
    Materie m2 = createMaterie("zahar", "Furnica", 30);
    Materie m4 = createMaterie("lamidon", "Furnica", 50);
    Materie m5 = createMaterie("sare", "Furnica", 100);

    assert(addMaterieSrv(&service, "lapte", "Napolact", 20) == true);
    Materie * repo = getRepoSrv(&service);
    assert(getLenRepo(&service) == 1);
    assert(equal(repo[0], m1));

    assert(addMaterieSrv(&service, "lapte", "Napolact", 200) == false);
    assert(addMaterieSrv(&service, "zahar", "", 200) == false);
    assert(addMaterieSrv(&service, "faina", "zuzu", -10) == false);

    assert(addMaterieSrv(&service, "zahar", "Furnica", 30) == true);
    repo = getRepoSrv(&service);
    assert(getLenRepo(&service) == 2);
    assert(equal(repo[0], m1));
    assert(equal(repo[1], m2));

    assert(updateMaterieSrv(&service, "lapte", "Zuzu", 2000) == true);
    repo = getRepoSrv(&service);
    assert(equal(repo[0], m1));
    assert(strcmp(getProducer(&repo[0]), "Zuzu") == 0);
    assert(getQuantity(&repo[0]) == 2000);

    assert(updateMaterieSrv(&service, "amidon", "Zuzu", 2000) == false);

    assert(deleteMaterieSrv(&service, "lapte") == true);
    repo = getRepoSrv(&service);
    assert(getLenRepo(&service) == 1);
    assert(equal(repo[0], m2));

    assert(deleteMaterieSrv(&service, "iaurt") == false);
    repo = getRepoSrv(&service);
    assert(getLenRepo(&service) == 1);
    assert(equal(repo[0], m2));

    assert(deleteMaterieSrv(&service, "zahar") == true);
    assert(getLenRepo(&service) == 0);

    assert(addMaterieSrv(&service, "lapte", "Napolact", 20) == true);
    assert(addMaterieSrv(&service, "zahar", "Furnica", 30) == true);
    assert(addMaterieSrv(&service, "lamidon", "Furnica", 50) == true);
    assert(addMaterieSrv(&service, "sare", "Furnica", 100) == true);

    MateriiRepo filter1 = filterByName(&service, 'l');
    assert(getLen(filter1) == 2);
    Materie *repo1 = getRepo(filter1);
    assert(equal(repo1[0], m1));
    assert(equal(repo1[1], m4));

    filter1 = filterByName(&service, 'x');
    assert(getLen(filter1) == 0);

    MateriiRepo filter2 = filterByProducer(&service, "Furnica");
    assert(getLen(filter2) == 3);
    Materie *repo2 = getRepo(filter2);
    assert(equal(repo2[0], m2));
    assert(equal(repo2[1], m4));
    assert(equal(repo2[2], m5));

    filter2 = filterByProducer(&service, "Panemar");
    assert(getLen(filter2) == 0);

    MateriiRepo filter3 = filterByQuantity(&service, 70);
    assert(getLen(filter3) == 3);
    Materie *repo3 = getRepo(filter3);
    assert(equal(repo3[0], m1));
    assert(equal(repo3[1], m2));
    assert(equal(repo3[2], m4));

    filter3 = filterByQuantity(&service, 3);
    assert(getLen(filter3) == 0);

    destroyService(&service);
}