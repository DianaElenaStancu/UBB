//
// Created by Diana-Elena Stancu on 20/04/2022.
//

#ifndef LAB07_UNDO_H
#define LAB07_UNDO_H
#include "domain.h"
#include "repository.h"

class ActiuneUndo
{
public:
    virtual void doUndo() = 0;

    virtual ~ActiuneUndo() {};
};

class UndoStore : public ActiuneUndo {
    Activitate activitate;
    Repository& repo;

public:
    UndoStore(Repository& repo, const Activitate& activitate) : activitate{ activitate }, repo{ repo }{};

    void doUndo() override;
};

class UndoErase : public ActiuneUndo {
    Activitate activitate;
    Repository& repo;

public:
    UndoErase(Repository& repo, const Activitate& activitate) : activitate{ activitate }, repo{ repo }{};

    void doUndo() override;
};

class UndoModify : public ActiuneUndo {
    Activitate activitate, activitate_noua;
    Repository& repo;

public:
    UndoModify(Repository& repo, const Activitate& activitate, const Activitate& activitate_noua) : activitate{ activitate }, activitate_noua{ activitate_noua }, repo{ repo }{};

    void doUndo() override;
};


#endif //LAB07_UNDO_H
