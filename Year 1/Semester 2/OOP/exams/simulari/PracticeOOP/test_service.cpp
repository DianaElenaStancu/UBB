//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#include "test_service.h"

void test_service::run_all() const {
    Repository repo;
    Validator val;
    Service service(repo, val);
    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
    Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};
    service.add("BC45DBF", "dacia", "logan", "berlina");
    try {
        service.add("BC45DBF", "dacia", "logan", "berlina");
        assert(false);
    } catch (const RepoException& ex) {
        stringstream out;
        out << ex;
        assert(ex.toString() == "Masina deja exista!\n");
        assert(true);
    }
    try {
        service.add("BC4", "dacia", "logan", "berlina");
        assert(false);
    } catch (const ValidatorException& ex) {
        stringstream out;
        out << ex;
        assert(ex.toString() == "nr inmatriculare invalid\n\n");
    }
}