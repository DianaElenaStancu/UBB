package com.example.examen.domain;

import java.util.List;

public class Event {

    private int count;
    private List<String> cities;

    private int clientId;

    public Event(int count, List<String> cities, int clientId) {
        this.count = count;
        this.cities = cities;
        this.clientId = clientId;
    }

    public int getClientId() {
        return clientId;
    }

    public void setClientId(int clientId) {
        this.clientId = clientId;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public List<String> getCities() {
        return cities;
    }

    public void setCities(List<String> cities) {
        this.cities = cities;
    }
}
