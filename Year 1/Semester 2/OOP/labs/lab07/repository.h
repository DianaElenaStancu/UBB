//
// Created by Diana-Elena Stancu on 06/04/2022.
//

#ifndef LAB07_REPOSITORY_H
#define LAB07_REPOSITORY_H
#include "domain.h"
#include "dynamic_array.h"
class Repository {
private:
    DynamicArray<Activitate>lista;
    bool exista(const Activitate& activitate) const;
public:
    //constructori
    Repository() = default;
    Repository(const Repository&) = delete;
    void add(const Activitate&);
    const Activitate& find(const Activitate&) const;
    unsigned int size() const noexcept;
    void remove(const Activitate&);
    const DynamicArray<Activitate>& getAll() const noexcept;
    void modify(Activitate& activitate, Activitate& activitate_noua);
};


#endif //LAB07_REPOSITORY_H
