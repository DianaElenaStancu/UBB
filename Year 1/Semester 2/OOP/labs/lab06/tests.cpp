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
        Repository<Activitate> repository;
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        assert(repository.size() == 0);
        Repository<Activitate> r1{a2};
        assert(r1.size() == 1);
        Repository<Activitate> r2(r1);
        assert(r2.size() == 1);
    }
    void add() override {
        Repository<Activitate> repository;
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
        Repository<Activitate> repository;
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        auto it = repository.find(a1);
        assert(it == nullptr);
        repository.add(a1);
        it = repository.find(a1);
        assert(*it == a1);
        try {
            cout << repository[1];
            assert(false);
        } catch (RepositoryException&) {assert(true);}
    };

    void remove() override {
        Repository<Activitate> repository;
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
        auto it = repository.find(a1);
        assert (it == nullptr);
        it = repository.find(a2);
        assert (*it == a2);
        repository.remove(a2);
        assert (repository.size() == 0);
    }

    void sort() override {
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Alergat", "2km in parcul central","Sport", 60);
        Activitate a3("Yoga", "in curte","Relax", 30);
        Repository<Activitate> repository;
        repository.add(a1);
        repository.add(a2);
        repository.add(a3);
        repository.sort();
        assert(repository[0] == a2);
        assert(repository[1] == a1);
        assert(repository[2] == a3);
    }

    void getters() override {

        Activitate a2("Alergat", "2km in parcul central","Sport", 60);
        Activitate a3("Yoga", "in curte","Relax", 30);
        Repository<Activitate> repository{a2, a3};
        for(Activitate x : repository){}
        for(Activitate& x : repository){}
        //for(const Activitate x: repository){}
        for(const Activitate& x: repository){}
        for(auto x : repository){}
        for(auto& x : repository){}
        //for(const auto x: repository){}
        for(const auto& x: repository){}
    }
};

class TestService : public Test {
protected:
    void add() override{
        Service service;
        service.addSRV("Citit", "Romanta", "Cultura", 120);
        Activitate a1("Citit", "Romanta", "Cultura", 120);

        assert(service.end() - service.begin() == 1);
        try {
            service.addSRV("Citit", "Romanta", "Cultura", 120);
            assert(false);
        } catch(RepositoryException&) {assert(true);}
        try {
            service.addSRV("", "Romanta", "Cultura", 120);
            assert(false);
        } catch(ValidatorException&) {assert(true);}
        assert(*service.begin() == a1);
    }

    void remove() override{
        Service service;
        try {
            service.removeSRV("Citit", "Romanta", "Cultura", 120);
            assert(false);
        } catch(RepositoryException&) { assert(true);}

        service.addSRV("Citit", "Romanta", "Cultura", 120);

        service.removeSRV("Citit", "Romanta", "Cultura", 120);

        assert(service.end() - service.begin() == 0);

        try {
            service.removeSRV("Citit", "Romanta", "Cultura", 0);
            assert(false);
        } catch(ValidatorException&) { assert(true);}
    }

    void modify() override{
        Service service;
        Activitate a1("Yoga", "in curte","Relax", 30);
        try {
            service.modifySRV("Citit", "Romanta", "Cultura", 120, "Citit", "Romanta", "Cultura", 120);
            assert(false);
        } catch(RepositoryException&) { assert(true);}

        service.addSRV("Citit", "Romanta", "Cultura", 120);
        service.modifySRV("Citit", "Romanta", "Cultura", 120, "Yoga", "in curte","Relax", 30);
        assert(*service.begin() == a1);
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
        Service service;
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        try {
            service.findSRV("Citit");
            assert(false);
        } catch(ServiceException&) { assert(true);}

        service.addSRV("Citit", "Romanta", "Cultura", 120);

        auto it = service.findSRV("Citit");
        assert(it == a1);
    }

    void filter() override{
        Service service;
        Activitate a1("Citit", "Romanta", "Cultura", 120);
        Activitate a2("Cantat", "Romanta", "Cardio", 120);
        Activitate a3("Alergat", "Sport", "Cardio", 60);
        service.addSRV("Citit", "Romanta", "Cultura", 120);
        service.addSRV("Cantat", "Romanta", "Cardio", 120);
        service.addSRV("Alergat", "Sport", "Cardio", 60);
        Repository <Activitate> repo;
        repo = service.filterDescriere("Romanta");
        assert(repo[0] == a1);
        assert(repo[1] == a2);
        try {
            service.filterDescriere("");
            assert(false);
        } catch(InvalidFieldException&) { assert(true);}
        repo = service.filterTip("Cardio");
        assert(repo[0] == a2);
        assert(repo[1] == a3);
        try {
            service.filterTip("");
            assert(false);
        } catch(InvalidFieldException&) { assert(true);}

        service.sortTitlu();
        assert(*service.begin() == a3);
        assert(*(service.begin()+1) == a2);
        assert(*(service.begin()+2) == a1);
        service.sortDescriere();
        assert(*service.begin() == a2);
        assert(*(service.begin()+1) == a1);
        assert(*(service.begin()+2) == a3);
        service.sortTipDurata();
        assert(*service.begin() == a3);
        assert(*(service.begin()+1) == a2);
        assert(*(service.begin()+2) == a1);
    }
    void getters() override{
        Service service;
        service.addSRV("Citit", "Romanta", "Cultura", 120);
        service.addSRV("Cantat", "Romanta", "Cardio", 120);
        service.addSRV("Alergat", "Sport", "Cardio", 120);
        for(Activitate x : service){}
        for(Activitate& x : service){}
        //for(const Activitate x: service){}
        for(const Activitate& x: service){}
        for(auto x : service){}
        for(auto& x : service){}
        //for(const auto x: service){}
        for(const auto& x: service){}
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
    TestRepository().run();
    TestService().run();
    TestExceptions().run();
    TestValidator().run();
}