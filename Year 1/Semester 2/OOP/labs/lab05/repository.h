//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#ifndef LAB05_REPOSITORY_H
#define LAB05_REPOSITORY_H
#include "infrastructure.h"

typedef struct _REPOSITORY_CHELTUIELI
{
    PDYNAMIC_VECTOR List;
    PDYNAMIC_VECTOR UndoList;
    int Count;
    int Size;
}REPOSITORY, * PREPOSITORY;

PREPOSITORY CreateRepository();
void DestroyRepository(PREPOSITORY Repository);
int InsertCheltuiala(PREPOSITORY Repository, TElem Cheltuiala);
int DeleteCheltuiala(PREPOSITORY Repository, int Id);

int ModifyCheltuiala(PREPOSITORY Repository, int Id, int NumarApartament, double Suma, char* Tip);

int UndoOperation(PREPOSITORY* Repository);

static void TestCreateAndDestroy();

static void TestInsert();

static void TestDelete();

static void TestModify();

static void TestSearch();

static void TestUndo();

void TestRepository();
#endif //LAB05_REPOSITORY_H
