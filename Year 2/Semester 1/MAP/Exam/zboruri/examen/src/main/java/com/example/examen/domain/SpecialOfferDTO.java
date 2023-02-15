package com.example.examen.domain;

import java.time.LocalDate;

public class SpecialOfferDTO extends Entity<Double>{
    private double specialOfferId;
    private String hotelName;
    private String locationName;

    private LocalDate startDate;
    private LocalDate endDate;

    public SpecialOfferDTO(double specialOfferId, String hotelName, String locationName, LocalDate startDate, LocalDate endDate) {
        super(specialOfferId);
        this.specialOfferId = specialOfferId;
        this.hotelName = hotelName;
        this.locationName = locationName;
        this.startDate = startDate;
        this.endDate = endDate;
    }

    public double getSpecialOfferId() {
        return specialOfferId;
    }

    public void setSpecialOfferId(double specialOfferId) {
        this.specialOfferId = specialOfferId;
    }

    public String getHotelName() {
        return hotelName;
    }

    public void setHotelName(String hotelName) {
        this.hotelName = hotelName;
    }

    public String getLocationName() {
        return locationName;
    }

    public void setLocationName(String locationName) {
        this.locationName = locationName;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDate startDate) {
        this.startDate = startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }

    @Override
    public String toString() {
        return "SpecialOfferDTO{" +
                "specialOfferId=" + specialOfferId +
                ", hotelName='" + hotelName + '\'' +
                ", locationName='" + locationName + '\'' +
                ", startDate=" + startDate +
                ", endDate=" + endDate +
                '}';
    }
}
