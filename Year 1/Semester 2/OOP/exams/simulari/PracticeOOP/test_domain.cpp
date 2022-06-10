//
// Created by Diana-Elena Stancu on 15/05/2022.
//

#include "test_domain.h"

void test_domain::test_get_set() const {
    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
    Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};
    assert(masina.GetNrInmatriculare() == "BC45DBF");
    assert(masina.GetProducator() == "dacia");
    assert(masina.GetModel() == "logan");
    assert(masina.GetTip() == "berlina");
    assert(masina != masina2);
}

void test_domain::test_print() const {
    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};

    stringstream os;
    os << masina;
    assert(os.str() == "BC45DBF | dacia | logan | berlina\n");
}

void test_domain::testIO() const {
    Masina masina{};

    ofstream out;
    out.open("testIO.out.", ios::out | ios::trunc);
    if (!out.is_open())
        return;
    Masina masina1{"BC45DBF", "dacia", "logan", "berlina"};
    out << masina1;
    Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};
    out << masina2;
    out.close();


    ifstream in("testIO.out", ios::in);
    if (!in.is_open())
            return;
    Masina m{};
    in >> m;
    assert(m.GetNrInmatriculare() == "BC45DBF");
    assert(m.GetProducator() == "dacia");
    assert(m.GetModel() == "logan");
    assert(m.GetTip() == "berlina");
}

void test_domain::run_all() const {
    test_get_set();
    test_print();
    testIO();
}