package com.example.templateexamen.Observer;

import java.util.ArrayList;
import java.util.List;

public abstract class AbstractObservable<E extends Event> implements Observable<E> {
    private List<Observer> observers = new ArrayList<>();

    public void addObserver(Observer<E> observer) {
        observers.add(observer);
    }

    public void removeObserver(Observer<E> observer) {
        observers.remove(observer);
    }

    public void notifyObservers(E event) {
        observers.forEach(observer -> observer.update(event));
    }
}
