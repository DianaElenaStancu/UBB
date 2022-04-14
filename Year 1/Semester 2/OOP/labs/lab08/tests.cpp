//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#include "tests.h"
#include <iostream>
using namespace std;

class TestDomain : public Test{
protected:
    void ctors() override {
        Activitate a1;
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        Activitate a3(a2);
        assert(a2 == a3);
        assert(a2 != a1);
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
        Activitate a2("Alergat", "2km", "Sport", 60);
        Activitate a3(a2);
        Activitate a4("Citit", "Romanta", "Cultura", 120);
        assert(a1 == Activitate());
        assert(a1 != a3);
        assert(a2 < a4);
        assert(!(a2 >= a4));
        assert(a2 <= a4);
        assert(! (a2 > a4));

        std::strstream sout;
        sout<<a2;
        sout>>a2;
        assert(a3 == a2);
    }
};

class TestRepository : public Test {
protected:
    void ctors() override {
        Repository repository;
        assert(repository.size() == 0);
    }
    void add() override {
        Repository repository;
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        repository.add(a1);
        assert(repository.size() == 1);
        repository.add(a2);
        assert(repository.size() == 2);
        try {
            repository.add(a2);
            assert(false);
        }
        catch (RepositoryException&) { assert(true);}
    }

    void find() override {
        Repository repository;
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        try {
            repository.find(a1);
            assert(false);
        } catch (RepositoryException&) {assert(true);}
        repository.add(a1);
        assert(repository.find(a1) == a1);
    };

    void remove() override {
        Repository repository;
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Alergat", "2km in parcul central","Sport", 60);
        try {
            repository.remove(a1);
            assert(false);
        }
        catch (RepositoryException&) { assert(true);}
        repository.add(a1);
        repository.add(a2);
        assert(repository.size() == 2);
        repository.remove(a1);
        assert (repository.size() == 1);
        try {
            repository.find(a1);
            assert(false);
        }
        catch (RepositoryException&) { assert(true);}
        assert (repository.find(a2) == a2);
        repository.remove(a2);
        assert (repository.size() == 0);
    }

    void modify() override {
        Repository repository;
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Alergat", "2km in parcul central","Sport", 60);
        repository.add(a1);
        repository.modify(a1, a2);
        assert(repository.find(a2) == a2);
    }
};

class TestService : public Test {
protected:
    void add() override{
        Repository repository{};
        Service service{repository};
        service.addSRV("Citit", "Romanta", "Cultura", 120);
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        try {
            service.addSRV("Citit", "Romanta", "Cultura", 120);
            assert(false);
        } catch(RepositoryException&) {assert(true);}
        try {
            service.addSRV("", "Romanta", "Cultura", 120);
            assert(false);
        } catch(ValidatorException&) {assert(true);}
        assert(repository.size() == 1);
    }

    void remove() override{
        Repository repository{};
        Service service{repository};
        try {
            service.removeSRV("Citit", "Romanta", "Cultura", 120);
            assert(false);
        } catch(RepositoryException&) { assert(true);}

        service.addSRV("Citit", "Romanta", "Cultura", 120);

        service.removeSRV("Citit", "Romanta", "Cultura", 120);

        assert(repository.size() == 0);

        try {
            service.removeSRV("Citit", "Romanta", "Cultura", 0);
            assert(false);
        } catch(ValidatorException&) { assert(true);}
    }

    void modify() override{
        Repository repository{};
        Service service{repository};
        Activitate a1("Yoga", "in curte","Relax", 30);
        try {
            service.modifySRV("Citit", "Romanta", "Cultura", 120, "Citit", "Romanta", "Cultura", 120);
            assert(false);
        } catch(RepositoryException&) { assert(true);}

        service.addSRV("Citit", "Romanta", "Cultura", 120);
        service.modifySRV("Citit", "Romanta", "Cultura", 120, "Yoga", "in curte","Relax", 30);

        vector<Activitate> lista{};
        lista = repository.getAll();
        assert(lista.at(0) == a1);

        try {
            service.modifySRV("Citit", "Romanta", "", 120, "Citit", "Romanta", "Cultura", 120);
            assert(false);
        } catch(ValidatorException&) { assert(true);}
        try {
            service.modifySRV("Citit", "Romanta", "Cultura", 120, "Citit", "", "Cultura", 120);
            assert(false);
        } catch(ValidatorException&) { assert(true);}
    }


    void find() override{
        Repository repository{};
        Service service{repository};
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        try {
            service.findSRV("Citit");
            assert(false);
        } catch(ServiceException&) { assert(true);}

        service.addSRV("Citit", "Romanta", "Cultura", 120);
        assert(service.findSRV("Citit") == a1);
    }

    void filter() override{
        Repository repository{};
        Service service{repository};
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Cantat", "Romanta", "Cardio", 120);
        Activitate a3("Alergat", "ASport", "Cardio", 60);
        service.addSRV("Citit", "Romanta", "Cultura", 120);
        service.addSRV("Cantat", "Romanta", "Cardio", 120);
        service.addSRV("Alergat", "ASport", "Cardio", 60);
        vector<Activitate> result{};
        result = service.filterDescriere("Romanta");
        assert(result.at(0) == a1);
        assert(result.at(1) == a2);
        try {
            service.filterDescriere("");
            assert(false);
        } catch(InvalidFieldException&) { assert(true);}
        result = service.filterTip("Cardio");
        assert(result.at(0) == a2);
        assert(result.at(1) == a3);
        try {
            service.filterTip("");
            assert(false);
        } catch(InvalidFieldException&) { assert(true);}

        vector<Activitate> result1{};
        result1 = service.sortTitlu();
        assert(result1.at(0) == a3);
        assert(result1.at(1) == a2);
        assert(result1.at(2) == a1);

        vector<Activitate> result2{service.sortDescriere()};
        result2 = service.sortDescriere();
        assert(result2.at(0) == a3);
        assert(result2.at(1) == a1);
        assert(result2.at(2) == a2);

        vector<Activitate> result3{service.sortTipDurata()};
        assert(result3.at(0) == a3);
        assert(result3.at(1) == a2);
        assert(result3.at(2) == a1);
    }

    void methods() override {
        Repository repository{};
        Service service{repository};
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Cantat", "Romanta", "Cardio", 120);
        Activitate a3("Alergat", "ASport", "Cardio", 60);

        try{service.genereazaLista(10); assert(false);}
        catch(...) {assert(true);}

        service.addSRV("Citit", "Romanta", "Cultura", 120);
        service.addSRV("Cantat", "Romanta", "Cardio", 120);
        service.addSRV("Alergat", "ASport", "Cardio", 60);
        vector<Activitate> r{service.getLista()};
        assert(r.empty());
        service.golesteLista();
        r = service.getLista();
        assert(r.empty());
        try{service.adaugaActivitate("a"); assert(false);}
        catch(...) {assert(true);}
        r = service.getLista();
        assert(r.empty());
        service.adaugaActivitate("Citit");
        service.adaugaActivitate("Alergat");
        r = service.getLista();
        assert(r.size() == 2);
        assert(r[0] == a1);
        assert(r[1] == a3);
        service.golesteLista();
        r = service.getLista();
        assert(r.empty());
        service.genereazaLista(10);
        r = service.getLista();
        assert(r.size() == 10);
        for (int i = 0; i < 10; i++)
            assert(r[i] == a1 || r[i] == a2 || r[i] == a3);

        //numara activitati
        assert(service.numara_activitati(100) == 1);
        assert(service.numara_activitati(130) == 3);
        assert(service.numara_activitati(0) == 0);
    }
};

class TestExceptions : public Test{
    void ctors() override{
        try {throw Exception("12");}
        catch(Exception& ex){ assert(strcmp(ex.what(), "12")==0);}
        try {throw RepositoryException("12");}
        catch(RepositoryException& ex){ assert(strcmp(ex.what(), "12")==0);}
        try {throw ServiceException("12");}
        catch(ServiceException& ex){ assert(strcmp(ex.what(), "12")==0);}
        try {throw InvalidFieldException("12");}
        catch(InvalidFieldException& ex){ assert(strcmp(ex.what(), "12")==0);}

        ValidatorException ve;
        InvalidFieldException ie("ex");
        vector<InvalidFieldException> vct{ie};
        ValidatorException ve2(vct);
        ValidatorException ve3(ve2);
        Exception me(ve);
        assert(strcmp(me.what(), ve.what()) == 0);
        assert(strcmp(ve3.what(), ve2.what()) == 0);
    }
    void operators() override{
        ValidatorException ve;
        InvalidFieldException ie("ex");
        vector<InvalidFieldException> vct{ie};
        ValidatorException ve2(vct);
        ValidatorException ve3(ve2);
        ve2 + ve3;
        ve2 + ie;
        ve2 + "Eroare la afisare!";
        ve2 += ve3;
        ve2 += ie;
        ve2 += "Eroare la afisare!";
        std::ostrstream out;
        out<<ve2 + "rip";
    }
};

class TestValidator : public Test{
    void methods() override{
        Activitate a("Citit", "Romanta", "Cultura", 120);
        Validator::validActivitate(a);
        try {Validator::validTitlu("1$$");assert(false);}
        catch(InvalidFieldException&){}
        try {Validator::validDescriere("-23");assert(false);}
        catch(InvalidFieldException&){}
        try {Validator::validTip("@"); assert(false);}
        catch(InvalidFieldException&){}
        try {Validator::validDurata(0);assert(false);}
        catch(InvalidFieldException&){}
        Activitate a1("*^%", "><", "", -120);
        try{Validator::validActivitate(a1);assert(false);}
        catch(ValidatorException& ve) { assert((int)ve == 4); }
    }
};


void TestAll() {
    TestDomain().run();
    TestExceptions().run();
    TestRepository().run();
    TestService().run();
    TestValidator().run();
}