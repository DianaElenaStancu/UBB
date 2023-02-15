package com.example.templateexamen.Observer.Example;

import com.example.templateexamen.Observer.Event;

public class ExampleEvent implements Event {
    private String information;

    public ExampleEvent(String information) {
        this.information = information;
    }

    public String getInformation() {
        return information;
    }
}
