//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#include "repository.hpp"

template<typename T>
typename vector <T>::iterator Repository<T>::getIterator(T* pointer ){
    return list.begin() + (pointer-list.data());
}

template <typename T>
Repository<T>::Repository(const Repository<T> & repo) {
    this->list = repo.list;
}

template <typename T>
Repository<T>::Repository(const std::initializer_list<T> & init_list) {
    for (const auto& elem: init_list)
        list.push_back(elem);
}

template<typename T>
int Repository<T>::size() const {
    return list.size();
}

template <typename T>
T& Repository<T>::operator[](const int & position) {
    if (position < list.size() && position >= 0)
        return list[position];
    throw RepositoryException("Pozitie invalida!\n");
}

template <typename T>
void Repository<T>::add(const T& element) {
    const T* it = find(element);
    if (it != NULL) throw RepositoryException("Elementul exista deja!\n");
//    try {
        list.push_back(element);
//    }
//    catch(...) {
//        throw RepositoryException("Elementul nu se poate adauga!\n");
//    }
}

template <typename T>
T* Repository<T>::find(const T& element, T* begin, T* end) {
    if(begin == NULL) begin = this->begin();
    if(end == NULL) end = this->end();
    for(auto it=begin; it != end; ++it)
        if(*it == element)
            return it;
    return NULL;
}


template<typename T> template<class UnaryPredicate>
T* Repository<T>::find(UnaryPredicate fct, T* begin, T* end) {
    if(begin == NULL) begin = this->begin();
    if(end == NULL) end = this->end();
    for(auto it=begin; it != end; ++it)
        if(fct(*it))
            return it;
    return NULL;
}

template <typename T>
void Repository<T>::remove(const T& element) {
    T* it = find(element);
    if (it == NULL)
        throw RepositoryException("Elementul nu se afla in lista!\n");
    list.erase(getIterator(it));
}

template<typename T> template<class Compare>
void Repository<T>::sort(Compare compare) {
    std::sort(list.begin(), list.end(), compare);
}

template<typename T>
T* Repository<T>::begin() { return list.begin().base();}

template<typename T>
T* Repository<T>::end() {return list.end().base(); }

//template<typename T>
//const T* Repository<T>::cbegin() const {return list.cbegin().base();}
//
//template<typename T>
//const T* Repository<T>::cend() const { return list.cend().base();}