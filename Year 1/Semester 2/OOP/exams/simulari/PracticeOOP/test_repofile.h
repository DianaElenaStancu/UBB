//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef PRACTICEOOP_TEST_REPOFILE_H
#define PRACTICEOOP_TEST_REPOFILE_H
#include "repofile.h"
#include <sstream>
using std::stringstream;

class test_repofile {
public:
    void run_all() {
        try {
            Repofile repo{"inexistent.txt"};
            assert(false);
        } catch(...) {
            assert(true);
        }
        string filename = "out.txt";
        Repofile repo{filename};
        Masina masina{"BC45DBF", "dacia", "logan", "berlina"};
        Masina masina2{"AG67SFF", "dacia", "logan", "berlina"};
        repo.erase(masina);
        repo.erase(masina2);
        repo.store(masina);
        repo.store(masina2);
        assert(repo.getLength() == 2);
        auto const all = repo.getAll();
        assert(all[0] == masina);
        assert(all[1] == masina2);
        repo.erase(masina);

        Repofile repo1{filename};
        assert(repo1.getLength() == 1);
        assert(repo1.find(masina2.GetNrInmatriculare()) == masina2);

        repo.store(masina);
    }


};


#endif //PRACTICEOOP_TEST_REPOFILE_H
