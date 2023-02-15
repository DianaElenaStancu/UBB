package com.example.templateexamen.Domain.Example;

import com.example.templateexamen.Domain.Entity;

public class ExampleEntity extends Entity<Integer> {
    private String name;
    public ExampleEntity(Integer id, String name) {
        super(id);
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
