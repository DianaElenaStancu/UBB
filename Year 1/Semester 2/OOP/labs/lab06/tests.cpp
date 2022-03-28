//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#include "tests.h"

class TestDomain : public Test{
protected:
    void ctors() override {
        Activitate a1;
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        Activitate a3(a2);
    }

    void getters() override {
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        assert(a2.getTitlu() == "Alergat");
        assert(a2.getDescriere() == "2km in parcul central");
        assert(a2.getTip() == "Sport");
        assert(a2.getDurata() == 60);
    }

    void setters() override {
        Activitate a1;
        assert(a1 == Activitate());
        a1.setTitlu("Citit");
        a1.setDescriere("Carte stiintifica");
        a1.setTip("Cultura");
        a1.setDurata(120);
        assert(a1 == Activitate("Citit", "Carte stiintifica", "Cultura", 120));
    }

    void operators() override {
        Activitate a1;
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        Activitate a3(a2);
        assert(a1 == Activitate());
        assert(a1 != a3);
    }
};

void TestAll() {
    TestDomain().run();
}