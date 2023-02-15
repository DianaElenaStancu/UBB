package com.example.examen.utils.observer;


import com.example.examen.utils.Event;

public interface Observable<E> {
    void addObserver(Observer<E> observer);
    void removeObserver(Observer<E> observer);
    void notifyObservers(E event);
}
