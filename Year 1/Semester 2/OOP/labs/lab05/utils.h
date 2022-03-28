//
// Created by Diana-Elena Stancu on 26/03/2022.
//

#ifndef LAB05_UTILS_H
#define LAB05_UTILS_H
#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "domain.h"
#include "infrastructure.h"

typedef int(*CompareFunction)(CHELTUIALA* t1, CHELTUIALA* t2);
typedef int (*AscendingMode)(int);
typedef int (*FilterFunction)(CHELTUIALA*);

int isInteger(char* text);

int isDouble(char* text);

void BubbleSort(PDYNAMIC_VECTOR List, CompareFunction cmpF, AscendingMode ascF);

int compareSuma(PCHELTUIALA t1, PCHELTUIALA t2);

int compareTip(PCHELTUIALA t1, PCHELTUIALA t2);

int ascendingMode(int result);

int descendingMode(int result);

int isType(PCHELTUIALA t, char* Tip);

int isSum(PCHELTUIALA t, double Sum);

int isNumber(PCHELTUIALA t, int Number);

int biggerSum(PCHELTUIALA t, double Suma);

int smallerSum(PCHELTUIALA t, double Suma);

void TestUtils();

#endif
#endif //LAB05_UTILS_H
