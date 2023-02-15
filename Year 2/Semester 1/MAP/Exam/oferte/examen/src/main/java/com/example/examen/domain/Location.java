package com.example.examen.domain;

public class Location extends Entity<Double>{
    private String locationaName;

    public Location(Double locationId, String locationaName) {
        super(locationId);
        this.locationaName = locationaName;
    }

    public String getLocationaName() {
        return locationaName;
    }

    public void setLocationaName(String locationaName) {
        this.locationaName = locationaName;
    }

    @Override
    public String toString() {
        return locationaName;
    }
}
