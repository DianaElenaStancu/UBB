//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "repository.h"
#include <stdio.h>

PREPOSITORY CreateRepository()
{
    PREPOSITORY Repository = malloc(sizeof(REPOSITORY));

    Repository->List = CreateList();
    Repository->UndoList = CreateList();

    return Repository;
}

void DestroyRepository(PREPOSITORY Repository)
{
    Destroy(Repository->List, DestroyCheltuiala);
    Destroy(Repository->UndoList, DestroyList);

    free(Repository);
}

int InsertCheltuiala(PREPOSITORY Repository, TElem Cheltuiala)
{
    DYNAMIC_VECTOR * Copy = CopyList(Repository->List);

    TElem CheltuialaFound;
    int count = GetLength(Repository->List);
    for (int i = 0; i < count; ++i)
    {
        CheltuialaFound = GetElement(Repository->List, i);
        if (GetId(CheltuialaFound) == GetId(Cheltuiala))
        {
            Destroy(Copy, DestroyCheltuiala);
            return -1;
        }
    }
    Insert(Repository->UndoList, Copy);

    Insert(Repository->List, Cheltuiala);

    return 0;
}

int DeleteCheltuiala(PREPOSITORY Repository, int Id)
{
    TElem Cheltuiala;
    int returnValue = -1;
    DYNAMIC_VECTOR * Copy = CopyList(Repository->List);

    int count = GetLength(Repository->List);
    for (int i = 0; i < count; ++i)
    {
        Cheltuiala = GetElement(Repository->List, i);
        if (GetId(Cheltuiala) == Id)
        {
            /*if (DestroyProdus(&(List->Array[i])) != 0)
            {
                return -1;
            }*/
            DestroyCheltuiala(Repository->List->Array[i]);
            for (int j = i; j < count - 1; ++j)
                Repository->List->Array[j] = Repository->List->Array[j + 1];
            returnValue = 0;
            Repository->List->Count = (Repository->List->Count) - 1;
            break;
        }
    }

    Redim(Repository->List);

    if (returnValue != -1)
    {
        Insert(Repository->UndoList, Copy);
    }
    else
    {
        Destroy(Copy, DestroyCheltuiala);
    }

    return returnValue;
}

int ModifyCheltuiala(PREPOSITORY Repository, int Id, int NumarApartament, double Suma, char* Tip)
{
    DYNAMIC_VECTOR * Copy = CopyList(Repository->List);

    TElem Cheltuiala;
    int count = GetLength(Repository->List);
    for (int i = 0; i < count; ++i)
    {
        Cheltuiala = GetElement(Repository->List, i);
        if (GetId(Cheltuiala) == Id)
        {
            SetNumarApartament((PCHELTUIALA)Cheltuiala, NumarApartament);
            SetSuma((PCHELTUIALA)Cheltuiala, Suma);
            SetTip((PCHELTUIALA)Cheltuiala, Tip);

            Insert(Repository->UndoList, Copy);
            return 0;
        }
    }
    Destroy(Copy, DestroyCheltuiala);
    return -1;
}

int UndoOperation(PREPOSITORY* Repository)
{
    if (GetLength((*Repository)->UndoList) == 0)
    {
        printf("no undos here");
        return -1;
    }

    DYNAMIC_VECTOR * Last = RemoveLast((*Repository)->UndoList);
    Destroy((*Repository)->List, DestroyCheltuiala);
    (*Repository)->List = Last;

    return 0;
}

static void TestCreateAndDestroy()
{
    PREPOSITORY Repo = CreateRepository();
    assert(GetLength(Repo->List) == 0);
    assert(GetLength(Repo->UndoList) == 0);

    DestroyRepository(Repo);
}

static void TestInsert()
{
    PREPOSITORY Repo = CreateRepository();

    TElem Cheltuiala1, Cheltuiala2, Cheltuiala3;
    Cheltuiala1 = CreateCheltuiala(6, 1, 200.34, "apa");
    assert(InsertCheltuiala(Repo, Cheltuiala1) == 0);
    assert(GetLength(Repo->List) == 1);

    assert(InsertCheltuiala(Repo, Cheltuiala1) == -1);

    Cheltuiala3 = CreateCheltuiala(7, 1, 200.34, "canal");
    assert(InsertCheltuiala(Repo, Cheltuiala3) == 0);
    assert(GetLength(Repo->List) == 2);

    for (int i = 0; i < 120; ++i)
    {
        Cheltuiala2 = CreateCheltuiala(i + 10, 1, 200.34, "apa");
        assert(InsertCheltuiala(Repo, Cheltuiala2) == 0);
        assert(GetLength(Repo->List) == i + 3);
    }

    assert(GetLength(Repo->List) == 122);

    DestroyRepository(Repo);
}

static void TestDelete()
{
    PREPOSITORY Repo = CreateRepository();

    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(6, 1, 200.34, "apa");
    assert(InsertCheltuiala(Repo, Cheltuiala) == 0);
    assert(GetLength(Repo->List) == 1);

    assert(DeleteCheltuiala(Repo, 6) == 0);
    assert(GetLength(Repo->List) == 0);

    assert(DeleteCheltuiala(Repo, 6) == -1);

    for (int i = 0; i < 120; ++i)
    {
        Cheltuiala = CreateCheltuiala(i + 10, 1, 200.34, "apa");
        assert(InsertCheltuiala(Repo, Cheltuiala) == 0);
    }
    for (int i = 0; i < 120; ++i)
    {
        assert(DeleteCheltuiala(Repo, i + 10) == 0);
        assert(GetLength(Repo->List) == 120 - i - 1);
    }

    assert(GetLength(Repo->List) == 0);

    DestroyRepository(Repo);
}

static void TestModify()
{
    PREPOSITORY Repo = CreateRepository();

    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(6, 1, 200.34, "apa");
    assert(InsertCheltuiala(Repo, Cheltuiala) == 0);

    assert(ModifyCheltuiala(Repo, 7, 1, 200.34, "apa") == -1);
    assert(ModifyCheltuiala(Repo, 6, 3, 300.244, "canal") == 0);

    TElem Result;
    assert(SearchCheltuiala(Repo->List, 6, &Result) == 0);

    Cheltuiala = CreateCheltuiala(6, 3, 300.244, "canal");
    assert(CheltuialaEqual(Cheltuiala, Result) == 1);

    DestroyCheltuiala(Cheltuiala);

    DestroyRepository(Repo);
}

static void TestSearch()
{
    DYNAMIC_VECTOR * List;
    List = CreateList();
    assert(GetLength(List) == 0);

    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(6, 3, 300.244, "canal");
    assert(Insert(List, Cheltuiala) == 0);

    TElem Result;
    assert(SearchCheltuiala(List, 6, &Result) == 0);
    assert(CheltuialaEqual(Result, Cheltuiala) == 1);

    assert(SearchCheltuiala(List, 9, &Result) == -1);

    for (int i = 0; i < 120; ++i)
    {
        Cheltuiala = CreateCheltuiala(i + 10, 3, 300.244, "canal");
        Insert(List, Cheltuiala);
    }

    for (int i = 0; i < 120; ++i)
    {
        assert(SearchCheltuiala(List, i + 10, &Result) == 0);
        assert(GetId(Result) == i + 10);
    }

    assert(Destroy(List, DestroyCheltuiala) == 0);
}

static void TestUndo()
{
    PREPOSITORY Repo = CreateRepository();

    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(6, 3, 300.244, "canal");
    assert(InsertCheltuiala(Repo, Cheltuiala) == 0);
    assert(GetLength(Repo->List) == 1);

    assert(UndoOperation(&Repo) == 0);
    assert(GetLength(Repo->List) == 0);
    assert(UndoOperation(&Repo) == -1);

    Cheltuiala = CreateCheltuiala(6, 3, 300.244, "canal");
    assert(InsertCheltuiala(Repo, Cheltuiala) == 0);
    assert(GetLength(Repo->List) == 1);

    for (int i = 0; i < 10; ++i)
    {
        Cheltuiala = CreateCheltuiala(i + 10, 3, 300.244, "canal");
        assert(InsertCheltuiala(Repo, Cheltuiala) == 0);
    }

    assert(GetLength(Repo->List) == 11);
    assert(UndoOperation(&Repo) == 0);
    assert(GetLength(Repo->List) == 10);

    assert(DeleteCheltuiala(Repo, 10) == 0);
    assert(GetLength(Repo->List) == 9);
    assert(UndoOperation(&Repo) == 0);
    assert(GetLength(Repo->List) == 10);

    assert(ModifyCheltuiala(Repo, 6, 5, 200.244, "apa") == 0);

    TElem Result;
    assert(SearchCheltuiala(Repo->List, 6, &Result) == 0);
    assert(GetSuma(Result) == 200.244);
    assert(GetNumarApartament(Result) == 5);
    assert(strcmp(GetTip(Result), "apa") == 0);

    assert(UndoOperation(&Repo) == 0);
    assert(SearchCheltuiala(Repo->List, 6, &Result) == 0);
    assert(GetSuma(Result) == 300.244);
    assert(GetNumarApartament(Result) == 3);
    assert(strcmp(GetTip(Result), "canal") == 0);

    DestroyRepository(Repo);
}

void TestRepository()
{
    TestCreateAndDestroy();
    TestInsert();
    TestDelete();
    TestModify();
    TestSearch();
    TestUndo();
}