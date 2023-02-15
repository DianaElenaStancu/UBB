package com.example.templateexamen.Validator;

import com.example.templateexamen.Exception.ValidationException;

public interface Validator<E> {
    void validate(E entity) throws ValidationException;
}