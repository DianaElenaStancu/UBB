//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#ifndef LAB05_INFRASTRUCTURE_H
#define LAB05_INFRASTRUCTURE_H
#ifndef _INFRASTRUCTURE_H_
#define _INFRASTRUCTURE_H_

#include <stdlib.h>
#include "domain.h"

typedef void* TElem;

#define INITIAL_SIZE 4
#define RC 2
#define RM 2
#define INPUT_SIZE 20

typedef struct _DYNAMIC_VECTOR
{
    TElem* Array;
    int Count;
    int Size;
}DYNAMIC_VECTOR, * PDYNAMIC_VECTOR;

typedef void (*DestroyFunction)(TElem);

DYNAMIC_VECTOR* CreateList();

TElem GetElement(PDYNAMIC_VECTOR List, int Position);

TElem SetElement(PDYNAMIC_VECTOR List, int Position, TElem Cheltuiala);

int SearchCheltuiala(PDYNAMIC_VECTOR List, int Id, TElem* Result);

void Redim(PDYNAMIC_VECTOR List);

int Insert(PDYNAMIC_VECTOR List, TElem Element);

int Delete(PDYNAMIC_VECTOR List, int Id, DestroyFunction destrF);

int ClearList(PDYNAMIC_VECTOR List, DestroyFunction destrF);

DYNAMIC_VECTOR* CopyList(PDYNAMIC_VECTOR List);

int GetLength(PDYNAMIC_VECTOR List);

TElem RemoveLast(PDYNAMIC_VECTOR List);

void MaintainListBelow(PDYNAMIC_VECTOR List);

void MaintainListAbove(PDYNAMIC_VECTOR List);

int Destroy(PDYNAMIC_VECTOR List, DestroyFunction destrF);

void DestroyList(DYNAMIC_VECTOR* List);

void TestInfrastructure();

#endif
#endif //LAB05_INFRASTRUCTURE_H
