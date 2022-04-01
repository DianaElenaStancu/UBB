//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#ifndef LAB06_REPOSITORY_HPP
#define LAB06_REPOSITORY_HPP

#include <type_traits>
#include <vector>
#include <algorithm>
#include "exceptions.h"
using std::vector;

template<typename T>

class Repository {
private:
    vector <T> list;
    typename vector <T>::iterator getIterator(T*);
public:
    //constructori
    Repository() = default;
    Repository(const Repository&);
    Repository(const std::initializer_list<T> &);

    //returneaza numarul de elemente din lista
    int size() const;

    //returneaza un pointer la un element cu pozitia data
    T& operator[](const int&);

    //adauga un element in lista
    void add(const T&);

    //cauta un element in lista
    T* find(const T&, T* = NULL, T* = NULL);

    template<class UnaryPredicate>
    T* find(UnaryPredicate, T* = NULL, T* = NULL);

    //sterge un element din lista
    void remove(const T&);

    //functie de sortare
    template<class Compare=std::less<T>>
    void sort(Compare compare = Compare{});

    // implementare iterator pentru lista
    T* begin();
    T* end();
/*    const T* cbegin() const;
    const T* cend() const;*/
};


#endif //LAB06_REPOSITORY_HPP
