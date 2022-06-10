//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "repository.h"

void Repository::load_data() {
    ifstream in(this->filename, std::ios::in);
    if (!in.is_open())
        return;
    if (in.peek() == ifstream::traits_type::eof())
        return;
    while(!in.eof()) {
        if (in.peek() == ifstream::traits_type::eof())
            return;
        Device device;
        in >> device;
        Repository::store(device);
    }
}

void Repository::store(Device &device) {
    storage.push_back(device);
}

vector <Device> Repository::get_all() const {
    return this->storage;
}