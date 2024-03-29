//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#ifndef LAB07_REPOSITORY_H
#define LAB07_REPOSITORY_H
#include "domain.h"
#include "exceptions.h"
#include <vector>
using std::vector;

class Repository {
private:
    vector<Activitate>lista;
    bool exista(const Activitate& activitate) const;
public:
    //constructori
    Repository() = default;
    Repository(const Repository&) = delete;
    virtual void add(const Activitate&);
    virtual const Activitate& find(const Activitate&) const;
    virtual unsigned int size() const noexcept;
    virtual void remove(const Activitate&);
    //const DynamicArray<Activitate>& getAll() const noexcept;
    virtual const vector<Activitate>& getAll() const noexcept;
    virtual void modify(Activitate& activitate, Activitate& activitate_noua);
};


#endif //LAB07_REPOSITORY_H
