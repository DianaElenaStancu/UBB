package com.example.examen.domain;

public class Location extends Entity<Double>{
    private Double locationId;
    private String locationName;

    public Location(Double locationId, String locationName) {
        super(locationId);
        this.locationId = locationId;
        this.locationName = locationName;
    }

    public Double getLocationId() {
        return locationId;
    }

    public void setLocationId(Double locationId) {
        this.locationId = locationId;
    }

    public String getLocationName() {
        return locationName;
    }

    public void setLocationName(String locationName) {
        this.locationName = locationName;
    }

    @Override
    public String toString() {
        return locationName;
    }
}
