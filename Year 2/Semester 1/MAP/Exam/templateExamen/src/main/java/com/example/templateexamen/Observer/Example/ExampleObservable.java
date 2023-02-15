package com.example.templateexamen.Observer.Example;

import com.example.templateexamen.Observer.AbstractObservable;

public class ExampleObservable extends AbstractObservable<ExampleEvent> {
    public void do_something() {
        notifyObservers(new ExampleEvent("Done something event"));
    }
}
/*
ExampleObservable observable = new ExampleObservable();

Observer<ExampleEvent> observer = new ExampleObserver();
Observer<ExampleEvent> observer2 = new ExampleObserver();

observable.addObserver(observer);
observable.addObserver(observer2);

observable.do_something();
 */
