package com.example.restaurante.utils.observer;

import com.example.restaurante.utils.utils.Event;

public interface Observer<E extends Event> {
    void update(E event);
}

