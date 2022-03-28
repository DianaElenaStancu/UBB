//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#include "utils.h"
#include "utils.h"

int isInteger(char* text)
{
    if (text == NULL)
    {
        return -1;
    }

    for (int i = 0; i < (int)strlen(text); ++i)
    {
        if (strchr("0123456789", text[i]) == NULL)
        {
            return 0;
        }
    }

    return 1;
}

int isDouble(char* text)
{
    if (text == NULL)
    {
        return -1;
    }

    int pointFound = 0;

    for (int i = 0; i < (int)strlen(text); ++i)
    {
        if (!pointFound && strchr(".", text[i]) != NULL)
        {
            pointFound ^= 1;
        }
        else if (strchr("0123456789", text[i]) == NULL)
        {
            return 0;
        }
    }

    return 1;
}

int compareTip(PCHELTUIALA t1, PCHELTUIALA t2) {
    if (strcmp(GetTip(t1), GetTip(t2)) == 0)
    {
        return 0;}
    else if (strcmp(GetTip(t1), GetTip(t2)) < 0)
    {
        return 1;
    }
    return -1;
}

int compareSuma(PCHELTUIALA t1, PCHELTUIALA t2) {
    if (GetSuma(t1) == GetSuma(t2))
    {
        return 0;
    }
    else if (GetSuma(t1) < GetSuma(t2))
    {
        return 1;
    }
    return -1;
}

int ascendingMode(int result) { return result; }

int descendingMode(int result) {
    if (!result)
    {
        return 0;
    }
    if (result == 1)
    {
        return -1;
    }
    return 1;
}

int isType(PCHELTUIALA t, char* Tip) {
    return strcmp(t->Tip, Tip) == 0;
}
int isSum(PCHELTUIALA t, double Sum) {
    return t->Suma == Sum;
}

int isNumber(PCHELTUIALA t, int Number) {
    return t->NumarApartament == Number;
}

int biggerSum(PCHELTUIALA t, double Suma) {
    return t->Suma > Suma;
}
int smallerSum(PCHELTUIALA t, double Suma) {
    return t->Suma < Suma;
}

void BubbleSort(PDYNAMIC_VECTOR List, CompareFunction cmpF, AscendingMode ascF)
{
    int length = GetLength(List);
    int change = 1;
    while (change == 1)
    {
        change = 0;
        for (int i = 0; i < length - 1; ++i)
        {
            TElem Cheltuiala1 = GetElement(List, i);
            TElem Cheltuiala2 = GetElement(List, i + 1);
            if (ascF(cmpF(Cheltuiala1, Cheltuiala2)) == -1)
            {
                SetElement(List, i, Cheltuiala2);
                SetElement(List, i + 1, Cheltuiala1);
                change = 1;
            }
        }
    }
}


static void TestFunctions()
{
    char* text = "123";
    assert(isInteger(text) == 1);

    text = "123.12";
    assert(isInteger(text) == 0);

    text = "text";
    assert(isInteger(text) == 0);

    text = "123";
    assert(isDouble(text) == 1);

    text = "123.12";
    assert(isDouble(text) == 1);

    text = "123.12.1";
    assert(isDouble(text) == 0);

    text = "text";
    assert(isDouble(text) == 0);

    assert(isInteger(NULL) == -1);
    assert(isDouble(NULL) == -1);

    TElem Cheltuiala = CreateCheltuiala(6, 5, 20.04, "apa");
    assert(isType(Cheltuiala, "apa") == 1);
    assert(isType(Cheltuiala, "") == 0);

    assert(smallerSum(Cheltuiala, 260) == 1);
    assert(smallerSum(Cheltuiala, 20.03) == 0);

    assert(biggerSum(Cheltuiala, 20.05) == 0);
    assert(biggerSum(Cheltuiala, 20.03) == 1);

    TElem CheltuialaNoua = CreateCheltuiala(6, 5, 20.045, "gaz");
    assert(compareSuma(Cheltuiala, CheltuialaNoua) == 1);
    assert(compareTip(Cheltuiala, CheltuialaNoua) == 1);

    DestroyCheltuiala(CheltuialaNoua);
    DestroyCheltuiala(Cheltuiala);
}

static void TestSort()
{
    DYNAMIC_VECTOR * Array = CreateList();
    TElem Cheltuiala;
    Cheltuiala = CreateCheltuiala(6, 5, 20.04, "apa");
    Insert(Array, Cheltuiala);

    TElem Cheltuiala1;
    Cheltuiala1 = CreateCheltuiala(7, 5, 30.04, "canal");
    Insert(Array, Cheltuiala1);
    assert(GetLength(Array) == 2);

    BubbleSort(Array, compareSuma, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);

    BubbleSort(Array, compareSuma, descendingMode);
    assert(GetId(GetElement(Array, 0)) == 7);
    assert(GetId(GetElement(Array, 1)) == 6);

    BubbleSort(Array, compareTip, ascendingMode);
    assert(GetId(GetElement(Array, 1)) == 7);
    assert(GetId(GetElement(Array, 0)) == 6);

    BubbleSort(Array, compareTip, descendingMode);
    assert(GetId(GetElement(Array, 0)) == 7);
    assert(GetId(GetElement(Array, 1)) == 6);


    TElem Cheltuiala2;
    Cheltuiala2 = CreateCheltuiala(8, 5, 0.04, "gaz");
    Insert(Array, Cheltuiala2);

    BubbleSort(Array, compareSuma, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 8);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 2)) == 7);

    BubbleSort(Array, compareSuma, descendingMode);
    assert(GetId(GetElement(Array, 2)) == 8);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 0)) == 7);

    BubbleSort(Array, compareTip, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);
    assert(GetId(GetElement(Array, 2)) == 8);

    Destroy(Array, DestroyCheltuiala);
}

void TestUtils()
{
    TestSort();
    TestFunctions();
}