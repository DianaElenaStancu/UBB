//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#include "exception.h"


const string Exception::toString() const {
    return this->message;
}

ostream& operator <<(ostream& out, const Exception& ex) {
    /*for (const auto& error: ex.message) {
        out << error;
    }*/
    out << ex.message;
    return out;
}

const string MultiStringException::toString() const {
    string result = "";
    for (const auto& str : errors) {
        result += str + "\n";
    }
    return result;
}

ostream& operator<<(ostream& out, const MultiStringException& val) {
    for(const auto& error: val.errors) {
        out << error;
    }
    return out;
}