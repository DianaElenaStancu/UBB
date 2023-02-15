package com.example.examen.utils.observer;

public interface Observable<E> {
    void addObserver(Observer<E> observer);
    void removeObserver(Observer<E> observer);
    void notifyObservers(E event);
}
