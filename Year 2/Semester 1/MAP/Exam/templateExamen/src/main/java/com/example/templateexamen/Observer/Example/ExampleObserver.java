package com.example.templateexamen.Observer.Example;

import com.example.templateexamen.Observer.Observer;

public class ExampleObserver implements Observer<ExampleEvent> {
    @Override
    public void update(ExampleEvent event) {
        System.out.println("i've been notified of the event: " + event.getInformation());
    }
}
