//
// Created by Diana-Elena Stancu on 05/03/2022.
//
#include <stdbool.h>
#include <string.h>

#include "validator.h"
#include "domain.h"

bool validate (Materie *m) {
    if (*m -> quantity < 0)
        return false;
    if (strlen (m -> name) == 0)
        return false;
    if (strlen (m -> producer) == 0)
        return false;
    return true;
}