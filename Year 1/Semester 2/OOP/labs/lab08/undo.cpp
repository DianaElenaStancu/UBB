//
// Created by Diana-Elena Stancu on 20/04/2022.
//

#include "undo.h"


void UndoStore::doUndo() {
    this->repo.remove(activitate);
}

void UndoErase::doUndo() {
    this->repo.add(activitate);
}


void UndoModify::doUndo() {
   this->repo.modify(activitate_noua, activitate);
}
