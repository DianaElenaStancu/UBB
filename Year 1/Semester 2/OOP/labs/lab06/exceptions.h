//
// Created by Diana-Elena Stancu on 29/03/2022.
//

#ifndef LAB06_EXCEPTIONS_H
#define LAB06_EXCEPTIONS_H

#include <exception>
#include <string>
#include <vector>
using std::exception;
using std::string;
using std::ostream;
using std::vector;

class Exception: public std::exception {
protected: // ca sa pot accesa in cadrul unei subclase
    string exc;
public:
    Exception(){ exc = "EXCEPTION!\n";}
    explicit Exception(const string& exc) : exc(exc) {}
    const char* what() const noexcept override {return exc.c_str();} //redefinesc o clasa
    friend ostream& operator<<(ostream& out, const Exception& excc) {out << excc.exc; return out;}
};

class RepositoryException : public Exception {using Exception::Exception;};
class ServiceException : public Exception {using Exception::Exception;};
class InvalidFieldException : public Exception { using Exception::Exception;};

class ValidatorException : public Exception {
private:
    string sep="\n";
    vector<InvalidFieldException> errors;
public:
    explicit ValidatorException()=default;//nu il pot folosit pentru conversii implicite si initializari de copiere
    explicit ValidatorException(const vector<InvalidFieldException> &errors_) : errors{errors_} {
        exc = "";
        for(const InvalidFieldException& ie : errors_)
            exc += ie.what() + sep;
    }
    ValidatorException(const ValidatorException& ve)=default;
    ValidatorException& operator=(const ValidatorException& ve) = default;
    friend ValidatorException operator+(const ValidatorException& ve1, const ValidatorException& ve2)
    {
        ValidatorException ve;
        ve.sep = ve1.sep;
        ve.errors.insert(ve.errors.end(), ve1.errors.cbegin(), ve1.errors.cend());
        ve.errors.insert(ve.errors.end(), ve2.errors.cbegin(), ve2.errors.cend());
        ve.exc = "";
        for(const InvalidFieldException& ie : ve.errors)
            ve.exc += ie.what() + ve.sep;
        return ve;
    }
    friend ValidatorException operator+(const ValidatorException& ve, const InvalidFieldException& ie)
    {
        vector<InvalidFieldException> vct{ie};
        ValidatorException ve2(vct);
        return ve + ve2;
    }
    friend ValidatorException operator+(const ValidatorException& ve, const string& msg)
    {
        return ve + InvalidFieldException(msg);
    }
    friend ValidatorException& operator+=(ValidatorException& ve1, const ValidatorException& ve2){
        ve1 = ve1 + ve2;
        return ve1;
    }
    friend ValidatorException& operator+=(ValidatorException& ve, const InvalidFieldException& ie)
    {
        ve = ve + ie;
        return ve;
    }
    friend ValidatorException& operator+=(ValidatorException& ve, const string& msg)
    {
        ve = ve + InvalidFieldException(msg);
        return ve;
    }
    explicit operator int() const {return (int)errors.size(); }
};
#endif //LAB06_EXCEPTIONS_H
