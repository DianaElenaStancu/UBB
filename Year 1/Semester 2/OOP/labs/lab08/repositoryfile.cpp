//
// Created by Diana-Elena Stancu on 20/04/2022.
//
#include "repositoryfile.h"
#include <iostream>
using namespace std;

double RepositoryProb::gen() const {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, 100);
    int r = dist(mt);
    double pb = double(r/100.0);
    return pb;
};

void RepositoryProb::add(const Activitate& activitate) {
    Repository::add(activitate);
    double pb = gen();
    cout << pb << endl;
    if (pb > prob) {
        throw RepositoryException("exception prob");
    }
    ++index;
    storage.insert(pair <int, Activitate>(index, activitate));
}

void RepositoryProb::remove(const Activitate& activitate) {
    Repository::remove(activitate);
    double pb = gen();
    cout << pb << endl;
    if (pb > prob) {
        throw RepositoryException("exception prob");
    }
    for (auto it = storage.begin(); it != storage.end(); it++) {
        if(it->second == activitate) {
            int in = it->first;
            storage.erase(in);
        }
    }

}

void RepositoryProb::modify(Activitate& activitate, Activitate& activitate_noua) {
    Repository::modify(activitate, activitate_noua);
    double pb = gen();
    cout << pb << endl;
    if (pb > prob) {
        throw RepositoryException("exception prob");
    }
    for (auto it = storage.begin(); it != storage.end(); it++) {
        if(it->second == activitate) {
            int in = it->first;
            storage.erase(in);
            storage.insert(pair <int, Activitate>(index, activitate_noua));
        }
    }
}

