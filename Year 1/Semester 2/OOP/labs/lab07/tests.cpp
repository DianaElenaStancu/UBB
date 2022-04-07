//
// Created by Diana-Elena Stancu on 27/03/2022.
//

#include "tests.h"
#include <iostream>
using namespace std;

class TestDynamicArray : public Test {
protected:
    void dynamic_array() override {
        DynamicArray<Activitate> array{};
        assert(array.size() == 0);

        Activitate a2("Alergat", "2km in parcul central", "Sport", 60);
        for (unsigned int i = 0; i < 100; ++i) {
            array.push_back(a2);
            assert(array.size() == i + 1);
        }
        assert(array.size() == 100);
        assert(array.at(0).getTitlu() == "Alergat");

        try {
            array.at(21234);
            assert(false);
        }
        catch (const OutOfRangeException& ex) {
        }
        array.erase(0);
        for (unsigned int i = 98; i > 0; --i) {
            array.erase(i);
        }
        assert(array.size() == 1);
        try {
            array.erase(21234);
            assert(false);
        }
        catch (const OutOfRangeException& ex) {
        }
    }
    void iterator() override {
        DynamicArray<Activitate> array{};
        assert(array.size() == 0);

        Activitate activitate{ "Alergat", "2km in parcul central", "Sport", 60 };
        array.push_back(activitate);
        Activitate activitate1{ "Cantat", "2km in parcul central", "Sport", 60};
        array.push_back(activitate1);

        DynamicArray<Activitate>::IteratorDynamicArray it = array.begin();
        assert(it.valid() == true);

        const Activitate& curr = it.element();
        assert(curr.getTitlu() == "Alergat");

        it.next();

        assert(it.valid() == true);
        const Activitate& curr1 = it.element();
        assert(curr1.getTitlu() == "Cantat");

        it.next();
        assert(it.valid() == false);

        try {
            it.element();
            assert(false);
        }
        catch (const OutOfRangeException& ex) {
            stringstream out;
            out << ex;
            assert(out.str() == "Iterator out of range!\n");
        }

        try {
            it.next();
            assert(false);
        }
        catch (const OutOfRangeException& ex) {
            stringstream out;
            out << ex;
            assert(out.str() == "Iterator out of range!\n");
        }

        const auto iter = array.begin();
        assert(iter.valid() == true);
        assert(iter.element().getTitlu() == "Alergat");

        const auto iterEnd = array.end();
        assert(iterEnd.valid() == false);

        //loop
        DynamicArray<Activitate> array1{};
        assert(array1.size() == 0);
        array1.push_back(activitate);
        array1.push_back(activitate1);

        int i = 1;
        for (const auto& elem : array1) {
            if (i == 1) {
                assert(elem.getTitlu() == "Alergat");
            }
            else {
                assert(elem.getTitlu() == "Cantat");
            }
            i = i + 1;
        }
    }
};
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

        DynamicArray<Activitate> lista{};
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
        DynamicArray<Activitate> result{};
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

        DynamicArray<Activitate> result1{};
        result1 = service.sortTitlu();
        assert(result1.at(0) == a3);
        assert(result1.at(1) == a2);
        assert(result1.at(2) == a1);

        DynamicArray<Activitate> result2{service.sortDescriere()};
        result2 = service.sortDescriere();
        assert(result2.at(0) == a3);
        assert(result2.at(1) == a1);
        assert(result2.at(2) == a2);

        DynamicArray<Activitate> result3{service.sortTipDurata()};
        assert(result3.at(0) == a3);
        assert(result3.at(1) == a2);
        assert(result3.at(2) == a1);
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
    TestDynamicArray().run();
    TestDomain().run();
    TestExceptions().run();
    TestRepository().run();
    TestService().run();

    TestValidator().run();
}