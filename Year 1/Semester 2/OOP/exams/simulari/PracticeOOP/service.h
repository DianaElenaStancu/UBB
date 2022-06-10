//
// Created by Diana-Elena Stancu on 16/05/2022.
//

#ifndef PRACTICEOOP_SERVICE_H
#define PRACTICEOOP_SERVICE_H
#include "validator.h"
#include "repository.h"
#include "undo.h"
#include <string>
using std::find;
class Service{
private:
    Repository& repo;
    const Validator& val;
    vector <std::unique_ptr<undo>> UndoActiune;
public:
    //Service() = default;
    Service(const Service& ot) = delete;
    Service(Repository& repo, Validator& val) noexcept : repo { repo }, val { val } {};
    void add(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);
    void del(const string& nrInmatriculare);
    void change(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);
    const Masina& find(const string& nrInmatriculare);
    const vector <Masina>& getAll() const noexcept;
    size_t getListSize() const noexcept;
    void clear();
    vector <Masina> filter(const string& filtru);
    void Undo();
};

class ServiceException : public Exception {
public:
    ServiceException(const string& message) : Exception(message) {};
};
#endif //PRACTICEOOP_SERVICE_H
