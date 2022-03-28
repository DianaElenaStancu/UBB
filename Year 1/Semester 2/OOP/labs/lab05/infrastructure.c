//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "infrastructure.h"
#include "infrastructure.h"

DYNAMIC_VECTOR* CreateList()
{
    DYNAMIC_VECTOR* List = malloc(sizeof(DYNAMIC_VECTOR));
    List->Array = (TElem*)malloc(INITIAL_SIZE * sizeof(TElem));
    List->Count = 0;
    List->Size = INITIAL_SIZE;

    return List;
}

TElem GetElement(PDYNAMIC_VECTOR List, int Position)
{
    return List->Array[Position];
}

TElem SetElement(PDYNAMIC_VECTOR List, int Position, TElem Cheltuiala)
{
    TElem Result = GetElement(List, Position);
    List->Array[Position] = Cheltuiala;
    return Result;
}

void Redim(PDYNAMIC_VECTOR List) {
    if (List->Count == List->Size)
        List->Size = List->Size * 2;
    else if (List->Size > INITIAL_SIZE && List->Size / List->Count > RM)
        List->Size = List->Size / RM;
    else
        return;
    TElem* temporary = (TElem*)malloc(sizeof(TElem) * List->Size);
    for (int i = 0; i < List->Count; ++i)
    {
        temporary[i] = List->Array[i];
    }
    free(List->Array);
    List->Array = temporary;
}


int Insert(PDYNAMIC_VECTOR List, TElem Element)
{
    Redim(List);

    List->Array[List->Count] = Element;
    List->Count = List->Count + 1;

    return 0;
}

int SearchCheltuiala(PDYNAMIC_VECTOR List, int Id, TElem* Result)
{
    TElem Cheltuiala;
    for (int i = 0; i < List->Count; ++i)
    {
        Cheltuiala = GetElement(List, i);
        if (GetId(Cheltuiala) == Id)
        {
            *Result = Cheltuiala;
            return 0;
        }
    }

    return -1;
}

int Delete(PDYNAMIC_VECTOR List, int Id, DestroyFunction destrF)
{
    TElem Cheltuiala;
    int returnValue = -1;
    for (int i = 0; i < List->Count; ++i)
    {
        Cheltuiala = GetElement(List, i);
        if (GetId(Cheltuiala) == Id)
        {
            /*if (DestroyProdus(&(List->Array[i])) != 0)
            {
                return -1;
            }*/
            destrF(List->Array[i]);
            for (int j = i; j < List->Count - 1; ++j)
                List->Array[j] = List->Array[j + 1];
            returnValue = 0;
            List->Count = (List->Count) - 1;
            break;
        }
    }

    Redim(List);

    return returnValue;
}

TElem RemoveLast(PDYNAMIC_VECTOR List)
{
    TElem last = GetElement(List, List->Count - 1);
    List->Count -= 1;
    return last;
}

int ClearList(PDYNAMIC_VECTOR List, DestroyFunction destrF)
{
    if (List == NULL)
    {
        return -1;
    }

    while (GetLength(List) > 0)
    {
        TElem Cheltuiala = GetElement(List, 0);
        /*if (DeleteProdus(List, id) != 0)
        {
            return -1;
        }*/
        Delete(List, GetId(Cheltuiala), destrF);
    }

    return 0;
}

DYNAMIC_VECTOR* CopyList(PDYNAMIC_VECTOR List)
{
    DYNAMIC_VECTOR* ListCopy;
    ListCopy = CreateList();

    int length = GetLength(List);
    TElem Cheltuiala;
    for (int i = 0; i < length; ++i)
    {
        Cheltuiala = GetElement(List, i);
        TElem CheltuialaInsert = CopyCheltuiala(Cheltuiala);
        Insert(ListCopy, CheltuialaInsert);
    }

    return ListCopy;
}

void DestroyList(DYNAMIC_VECTOR* List)
{
    Destroy(List, DestroyCheltuiala);
}

int Destroy(PDYNAMIC_VECTOR List, DestroyFunction destrF) {
    if (List == NULL)
    {
        return -1;
    }

    /*if (ClearList(*List) != 0)
    {
        return -1;
    }*/
    int count = GetLength(List);
    for (int i = 0; i < count; ++i)
    {
        TElem Element = GetElement(List, i);
        destrF(Element);
    }

    free(List->Array);
    free(List);

    return 0;
}

int GetLength(PDYNAMIC_VECTOR List)
{
    return List->Count;
}

static void TestCreateAndDestroy()
{
    DYNAMIC_VECTOR* List;

    List = CreateList();
    assert(GetLength(List) == 0);

    assert(Destroy(NULL, DestroyList) == -1);
    assert(Destroy(List, DestroyList) == 0);
}

static void TestInsert()
{
    DYNAMIC_VECTOR* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    TElem Cheltuiala1, Cheltuiala2, Cheltuiala3;
    Cheltuiala1 = CreateCheltuiala(6, 1, 200.34, "apa");
    assert(Insert(List, Cheltuiala1) == 0);
    assert(GetLength(List) == 1);

    Cheltuiala3 = CreateCheltuiala(7, 10, 23400.34, "gaz");
    assert(Insert(List, Cheltuiala3) == 0);
    assert(GetLength(List) == 2);

    TElem Result;
    Result = GetElement(List, 1);
    assert(CheltuialaEqual(Result, Cheltuiala3) == 1);

    TElem CheltuialaNoua = CreateCheltuiala(70, 170, 80, "canal");
    Result = SetElement(List, 1, CheltuialaNoua);
    assert(CheltuialaEqual(Result, Cheltuiala3) == 1);
    DestroyCheltuiala(Result);

    Result = GetElement(List, 1);
    assert(CheltuialaEqual(Result, CheltuialaNoua) == 1);

    for (int i = 0; i < 120; ++i)
    {
        Cheltuiala2 = CreateCheltuiala(i+200, 170, 80, "canal");
        assert(Insert(List, Cheltuiala2) == 0);
        assert(GetLength(List) == i + 3);
    }

    assert(GetLength(List) == 122);
    assert(Destroy(List, DestroyCheltuiala) == 0);
}

static void TestSearch()
{
    DYNAMIC_VECTOR* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(0, 170, 80, "canal");
    assert(Insert(List, Cheltuiala) == 0);

    TElem Result;
    assert(SearchCheltuiala(List, 0, &Result) == 0);
    assert(CheltuialaEqual(Result, Cheltuiala) == 1);

    assert(SearchCheltuiala(List, 9, &Result) == -1);

    for (int i = 0; i < 120; ++i)
    {
        Cheltuiala = CreateCheltuiala(i+10, 170, 80, "canal");
        Insert(List, Cheltuiala);
    }

    for (int i = 0; i < 120; ++i)
    {
        assert(SearchCheltuiala(List, i + 10, &Result) == 0);
        assert(GetId(Result) == i + 10);
    }

    assert(Destroy(List, DestroyCheltuiala) == 0);
}

static void TestDelete()
{
    DYNAMIC_VECTOR* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(70, 170, 80, "canal");
    assert(Insert(List, Cheltuiala) == 0);
    assert(GetLength(List) == 1);

    assert(Delete(List, 70, DestroyCheltuiala) == 0);
    assert(GetLength(List) == 0);

    assert(Delete(List, 6, DestroyCheltuiala) == -1);

    for (int i = 0; i < 120; ++i)
    {
        Cheltuiala = CreateCheltuiala(i+10, 170, 80, "canal");
        assert(Insert(List, Cheltuiala) == 0);
    }
    for (int i = 0; i < 120; ++i)
    {
        assert(Delete(List, i + 10, DestroyCheltuiala) == 0);
        assert(GetLength(List) == 120 - i - 1);
    }

    assert(GetLength(List) == 0);

    assert(Destroy(List, DestroyCheltuiala) == 0);
}

static void TestClear()
{
    DYNAMIC_VECTOR* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    TElem Cheltuiala;

    for (int i = 0; i < 120; ++i)
    {
        Cheltuiala = CreateCheltuiala(i, 170, 80, "canal");
        assert(Insert(List, Cheltuiala) == 0);
    }
    assert(GetLength(List) == 120);
    assert(ClearList(NULL, DestroyCheltuiala) == -1);

    assert(ClearList(List, DestroyCheltuiala) == 0);
    assert(GetLength(List) == 0);

    assert(Destroy(List, DestroyCheltuiala) == 0);
}

static void TestCopyList()
{
    TElem* Result = (TElem*)malloc(sizeof(TElem));
    TElem* Result1 = (TElem*)malloc(sizeof(TElem));

    DYNAMIC_VECTOR* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(70, 170, 80, "canal");
    assert(Insert(List, Cheltuiala) == 0);

    TElem CheltuialaNoua;
    CheltuialaNoua = CreateCheltuiala(10, 170, 80, "canal");
    assert(Insert(List, CheltuialaNoua) == 0);

    DYNAMIC_VECTOR* ListCopy;
    ListCopy = CopyList(List);
    assert(SearchCheltuiala(List, 70, Result) == 0);
    assert(SearchCheltuiala(ListCopy, 70, Result1) == 0);
    assert(CheltuialaEqual(*Result, *Result1) == 1);
    assert(SearchCheltuiala(List, 70, Result) == 0);
    assert(SearchCheltuiala(ListCopy, 70, Result1) == 0);
    assert(CheltuialaEqual(*Result, *Result1) == 1);

    assert(Destroy(List, DestroyCheltuiala) == 0);
    assert(Destroy(ListCopy, DestroyCheltuiala) == 0);

    free(Result);
    free(Result1);
}

static void TestListeDeListe()
{
    DYNAMIC_VECTOR* List = CreateList();
    Insert(List, CreateCheltuiala(5, 170, 80, "canal"));
    Insert(List, CreateCheltuiala(9, 170, 80, "canal"));

    DYNAMIC_VECTOR* List1 = CreateList();
    DYNAMIC_VECTOR* UndoL = CreateList();
    Insert(UndoL, List);
    assert(GetLength(UndoL) == 1);
    Insert(UndoL, List1);
    assert(GetLength(UndoL) == 2);

    Destroy(UndoL, DestroyList);
}

void TestInfrastructure()
{
    TestCreateAndDestroy();
    TestInsert();
    TestSearch();
    TestDelete();
    TestClear();
    TestCopyList();
    TestListeDeListe();
}