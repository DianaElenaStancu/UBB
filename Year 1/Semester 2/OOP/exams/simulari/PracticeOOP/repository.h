//
// Created by Diana-Elena Stancu on 15/05/2022.
//

#ifndef PRACTICEOOP_REPOSITORY_H
#define PRACTICEOOP_REPOSITORY_H
#include "domain.h"
#include "exception.h"
#include <vector>
using std::vector;

class Repository {
private:
    vector <Masina> storage;
    bool exista(const Masina& masina) const;
public:
    Repository() = default;
    Repository(const Repository& ot) = delete;

    virtual void store(const Masina& masina);
    virtual void erase(const Masina& masina);
    virtual  const Masina& find(const string& nrInmatriculare) const;
    virtual void modify(const Masina& masinaModify);
    const vector<Masina>& getAll() const noexcept;
    const unsigned int getLength() const noexcept;
    void clear() noexcept;
    friend ostream& operator<<(ostream& out, const Repository& repo);
};

class RepoException : public Exception {
public:
    RepoException(const string& message) : Exception(message) {};
};


#endif //PRACTICEOOP_REPOSITORY_H
