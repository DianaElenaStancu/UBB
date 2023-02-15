package com.example.examen.domain.validators;

import com.example.examen.domain.Persoana;

import java.util.Objects;

public class ValidatorPersoana implements  Validator<Persoana>{
    @Override
    public void validate(Persoana entity) throws ValidationException {
        String errorMessage = "";
        if(Objects.equals(entity.getNume(), "") || Objects.equals(entity.getPrenume(), "") ||
        Objects.equals(entity.getParola(), "") || Objects.equals(entity.getStrada(), "") ||
                Objects.equals(entity.getTelefon(), "")) {
            errorMessage += "Fielduri goale!\n";
        }
        if(errorMessage.length() > 0) {
            throw new ValidationException(errorMessage);
        }
    }
}
