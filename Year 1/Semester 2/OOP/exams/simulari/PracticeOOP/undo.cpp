//
// Created by Diana-Elena Stancu on 17/05/2022.
//

#include "undo.h"

void undoAdd::doUndo() {
    this->repo.erase(masina);
}

void undoRemove::doUndo() {
    this->repo.store(masina);
}


void undoModify::doUndo() {
    this->repo.modify(masina);
}


void undoClear::doUndo() {
    for (auto const &m: this->masini)
        this->repo.store(m);
}