//
// Created by Diana-Elena Stancu on 16/03/2022.
//

#include "utils.h"

void BubbleSort(MATERIE_P Array, Cmp cmp, int len) {
    if (len <= 1) return ;
    bool sort = 0;
    while (!sort) {
        sort = 1;
        for (int i = 0; i < len - 1; i++) {
            if (!cmp(Array[i], Array[i + 1])) {
                MATERIE m = Array[i];
                Array[i] = Array[i + 1];
                Array[i + 1] = m;
                sort = 0;
            }
        }
    }
}

void SelectionSort(MATERIE_P Array, Cmp cmp, int len)
{
    for(int i = 0;i < len;++i)
        for (int j = i + 1; j < len; ++j)
        {
            if (!cmp(Array[i], Array[j]) > 0)
            {
                MATERIE m = Array[i];
                Array[i] = Array[j];
                Array[j] = m;
            }
        }
}
