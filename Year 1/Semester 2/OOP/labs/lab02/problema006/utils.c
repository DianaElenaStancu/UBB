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
