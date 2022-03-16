//
// Created by Diana-Elena Stancu on 16/03/2022.
//

#ifndef PROBLEMA006_UTILS_H
#define PROBLEMA006_UTILS_H
#include "domain.h"
typedef bool(*Cmp)(MATERIE m1, MATERIE m2);

/*
 * functia sorteaza array-ul de materii prime
 *
 *
 */
void BubbleSort(MATERIE_P Array, Cmp cmp, int len);
#endif //PROBLEMA006_UTILS_H
