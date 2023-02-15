package com.example.examen.domain.validators;

import java.time.LocalDateTime;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}

/*
to implement:

public class NameValidator implements Validator<...> {

    public void validate(...) {
        String errorMessage = "";
        if() {
            errorMessage += "\n";
        }
        if(errorMessage.length() > 0) {
            throw new ValidationException(errorMessage);
        }
    }
}
 */