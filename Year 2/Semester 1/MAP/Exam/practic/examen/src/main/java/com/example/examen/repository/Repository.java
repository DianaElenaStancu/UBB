package com.example.examen.repository;


import com.example.examen.domain.Entity;

public interface Repository<ID, E extends Entity<ID>> {

    Iterable<E> findAll();
}
