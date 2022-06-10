//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#ifndef PRACTICEOOP_EXCEPTION_H
#define PRACTICEOOP_EXCEPTION_H
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::ostream;

class Exception {
    string message;
public:
    Exception(string message) : message { message } {};
    const string toString() const;
    friend ostream& operator <<(ostream& out, const Exception& ex);
};

class MultiStringException {
    vector <string> errors;
public:
    MultiStringException(const vector <string>& errors) : errors{ errors } {};

    const string toString() const;

    friend ostream& operator<<(ostream& out, const MultiStringException& val);
};
#endif //PRACTICEOOP_EXCEPTION_H
