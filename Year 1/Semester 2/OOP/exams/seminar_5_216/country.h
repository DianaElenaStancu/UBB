//
// Created by Mali Imre Gergely on 04.05.2022.
//

#ifndef SEMINAR_EXAMPLE_COUNTRY_H
#define SEMINAR_EXAMPLE_COUNTRY_H

#include <string>

using std::string;

class Country {
    std::string name;
    std::string capital;
    int population;
public:
    Country() = default;

    Country(const string &name, const string &capital, int population) :
            name{name},
            capital{capital},
            population{population} {}

    bool operator==(const Country &other) {
        return this->name == other.name;
    }

    string get_name() const { return this->name; }

    string get_capital() const { return this->capital; }

    int get_population() const { return this->population; }

};


#endif //SEMINAR_EXAMPLE_COUNTRY_H
