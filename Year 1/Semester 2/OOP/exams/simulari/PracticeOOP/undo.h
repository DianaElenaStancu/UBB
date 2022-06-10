//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#ifndef PRACTICEOOP_UNDO_H
#define PRACTICEOOP_UNDO_H
#include "repository.h"

class undo {
public:
    virtual void doUndo() = 0;
    virtual ~undo(){};
};

class undoAdd : public undo {
private:
    Masina masina;
    Repository& repo;
public:
    undoAdd(Repository &repo, const Masina &masina) : masina{ masina }, repo { repo } {};
    void doUndo() override;
};

class undoRemove : public undo {
private:
    Masina masina;
    Repository& repo;
public:
    undoRemove(Repository &repo, const Masina &masina) : masina{ masina }, repo { repo } {};
    void doUndo() override;
};

class undoModify : public undo {
private:
    Masina masina;
    Repository& repo;
public:
    undoModify(Repository &repo, const Masina &masina) :  masina{ masina }, repo { repo } {};
    void doUndo() override;
};

class undoClear : public undo {
private:
    vector <Masina> masini;
    Repository& repo;
public:
    undoClear(Repository &repo, const vector <Masina> masini) : masini { masini }, repo { repo } {};
    void doUndo() override;
};
#endif //PRACTICEOOP_UNDO_H
