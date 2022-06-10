//
// Created by Diana-Elena Stancu on 18/05/2022.
//

#include "validator.h"

bool Validator::validate_placa(PlacaDeBaza &placa) const {
    if (placa.get_nume() == "")
        return false;
    if (placa.get_pret() <= 0)
        return false;
    if (placa.get_soclu() == "")
        return false;
    return true;
}