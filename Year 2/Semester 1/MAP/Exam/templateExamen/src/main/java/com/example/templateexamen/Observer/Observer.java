package com.example.templateexamen.Observer;

public interface Observer<E extends Event> {
    void update(E event);
}