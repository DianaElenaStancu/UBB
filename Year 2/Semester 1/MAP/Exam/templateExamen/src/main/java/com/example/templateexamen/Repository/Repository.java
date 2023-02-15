package com.example.templateexamen.Repository;

import com.example.templateexamen.Domain.Entity;

import java.net.URL;

public interface Repository<ID, E extends Entity<ID>> {
    E findOne(ID id);

    Iterable<E> findAll();

    void save(E entity);

    void delete(ID id);

    void update(E entity);

    void validate(E entity);
}
