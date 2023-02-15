package com.example.restaurante.domain;

import java.util.Objects;

public class Table extends Entity<Integer> {

    public Table(int id) {
        super(id);
    }

    @Override
    public String toString() {
        return "Table{" +
                "id=" + getId() +
                '}';
    }
}
