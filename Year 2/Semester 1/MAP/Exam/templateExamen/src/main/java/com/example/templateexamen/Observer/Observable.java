package com.example.templateexamen.Observer;

public interface Observable<E extends Event> {
    void addObserver(Observer<E> observer);

    void removeObserver(Observer<E> observer);

    void notifyObservers(E observer);
}

