//
// Created by Mali Imre Gergely on 04.05.2022.
//

#ifndef SEMINAR_EXAMPLE_REPOSITORY_H
#define SEMINAR_EXAMPLE_REPOSITORY_H

#include <vector>
#include <algorithm>

using std::vector;

template<typename T>
class Repository {
    vector<T> elems;
public:
    Repository() = default;

    Repository(const Repository<T> &other) = delete;

    void add(const T &elem) {
        auto found_elem = std::find(this->elems.begin(), this->elems.end(), elem);
        if (found_elem != this->elems.end()) {
            throw std::runtime_error("Element already exists");
        }
        elems.push_back(elem);
    }

    void remove(const T &elem) {
        this->elems.erase(std::find(this->elems.begin(), this->elems.end(), elem));
    }

    T &find(const T &elem) {
        auto found_elem = std::find(this->elems.begin(), this->elems.end(), elem);
        if (found_elem == this->elems.end()) {
            throw std::runtime_error("Element does not exist");
        }
        return *found_elem;
    }

    void update(const T &elem) {
        T &found = this->find(elem);
        found = elem;
    }

    vector<T> &get_all() {
        return this->elems;
    }
};


#endif //SEMINAR_EXAMPLE_REPOSITORY_H
