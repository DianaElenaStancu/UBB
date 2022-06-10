//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#include "test_repo.h"

void test_repo::test_store() const{
    Repository repo;
    assert(repo.getLength() == 0);

    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
    Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};
    repo.store(masina);
    assert(repo.getLength() == 1);
    try {
        repo.store(masina);
        assert(false);
    }
    catch(const RepoException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Masina deja exista!\n");
        assert(true);
    }
    repo.store(masina2);
    assert(repo.getLength() == 2);
}

void test_repo::test_erase() const{
    Repository repo;
    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
    Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};

    try {
        repo.erase(masina);
        assert(false);
    }
    catch(const RepoException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Masina inexistenta!\n");
        assert(true);
    }

    repo.store(masina);
    repo.store(masina2);
    repo.erase(masina);
    assert(repo.getLength() == 1);
    try {
        repo.erase(masina);
        assert(false);
    }
    catch(const RepoException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Masina inexistenta!\n");
        assert(true);
    }
    repo.erase(masina2);
    assert(repo.getLength() == 0);
}

void test_repo::test_modify() const{
    Repository repo;
    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
    Masina masina1{"BC45DBF", "porsche", "cayanne", "de smecheri"};
    Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};
    try {
        repo.modify(masina);
        assert(false);
    }
    catch(const RepoException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Masina inexistenta!\n");
        assert(true);
    }
    repo.store(masina);
    try {
        repo.modify(masina2);
        assert(false);
    }
    catch(const RepoException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "Masina inexistenta!\n");
        assert(true);
    }
    repo.modify(masina1);
    auto masinaGasita = repo.find(masina1.GetNrInmatriculare());
    assert(masinaGasita.GetNrInmatriculare() == "BC45DBF");
    assert(masinaGasita.GetProducator() == "porsche");
    assert(masinaGasita.GetModel() == "cayanne");
    assert(masinaGasita.GetTip() == "de smecheri");
}

void test_repo::test_find() const{

}
void test_repo::test_print() const{
    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
    Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};
    Repository repo;
    repo.store(masina);
    repo.store(masina2);
    stringstream os;
    os << repo;
    assert(os.str() == "BC45DBF | dacia | logan | berlina\nAG67SFF | dacia | logan | berlina\n");
}
void test_repo::run_all() const{
    test_store();
    test_print();
    test_erase();
    test_find();
    test_modify();
}