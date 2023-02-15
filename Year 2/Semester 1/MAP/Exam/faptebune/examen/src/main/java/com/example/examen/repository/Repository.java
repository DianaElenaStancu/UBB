package com.example.examen.repository;


import com.example.examen.domain.Entity;

public interface Repository<ID, E extends Entity<ID>> {
    E findOne(ID id);

    Iterable<E> findAll();

    void save(E entity);

    void delete(ID id);

    void update(E entity);

    void validate(E entity);
}
