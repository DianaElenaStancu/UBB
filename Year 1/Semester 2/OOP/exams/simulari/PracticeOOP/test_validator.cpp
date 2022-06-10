//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#include "test_validator.h"

void test_validator::run_all() const {
    Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
    Masina masina2{"AG67SFsaF", "dacia", "", "berlina"};
    Validator val;
    val.validate(masina);
    try {
        val.validate(masina2);
        assert(false);
    } catch(const ValidatorException& ex) {
        stringstream out;
        out << ex;
        assert(out.str() == "nr inmatriculare invalid\nmodel invalid\n");
    }
}