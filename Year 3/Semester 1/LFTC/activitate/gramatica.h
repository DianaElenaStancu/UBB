//
// Created by Diana-Elena Stancu on 15.12.2023.
//

#ifndef ACTIVITATE_GRAMATICA_H
#define ACTIVITATE_GRAMATICA_H
#include <string>
#include <vector>
using namespace std;

class gramatica {
private:
    vector<char> terminale;
    vector<char> neterminale;
    vector<string> reguliProductie;
public:
    const vector<char> &getTerminale() const {
        return terminale;
    }

    void setTerminale(const vector<char> &terminale) {
        gramatica::terminale = terminale;
    }

    const vector<char> &getNeterminale() const {
        return neterminale;
    }

    void setNeterminale(const vector<char> &neterminale) {
        gramatica::neterminale = neterminale;
    }

    const vector<string> &getReguliProductie() const {
        return reguliProductie;
    }

    void setReguliProductie(const vector<string> &reguliProductie) {
        gramatica::reguliProductie = reguliProductie;
    }
};


#endif //ACTIVITATE_GRAMATICA_H
