//
// Created by Mali Imre Gergely on 04.05.2022.
//

#ifndef SEMINAR_EXAMPLE_SERVICE_H
#define SEMINAR_EXAMPLE_SERVICE_H

#include <string>
#include <vector>
#include "country.h"
#include "repository.h"

using std::string;
using std::vector;

class Service {
    Repository<Country> &repo;
public:
    Service(Repository<Country> &repo) : repo{repo} {}

    Service(const Service &other) = delete;

    void add(const string &name, const string &capital, int population) {
        this->repo.add(Country(name, capital, population));
    }

    void remove(const std::string &name) {
        this->repo.remove(Country(name, "", 0));//TODO
    }

    Country find(const std::string &name) {
        return this->repo.find(Country(name, "", 0));
    }

    void update(const string &name, const string &capital, int population) {
        this->repo.update(Country(name, capital, population));
    }

    vector<Country> &get_all() {
        return this->repo.get_all();
    }

    vector<Country> find_by_population(int population) {
        auto elements = this->get_all();
        std::vector<Country> filtered;
        std::copy_if(elements.begin(),
                     elements.end(),
                     std::back_inserter(filtered),
                     [population](Country &c) { return c.get_population() > population; });

        return filtered;
    }

};


#endif //SEMINAR_EXAMPLE_SERVICE_H
