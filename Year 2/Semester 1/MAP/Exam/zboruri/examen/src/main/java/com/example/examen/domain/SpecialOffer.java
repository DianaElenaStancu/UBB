package com.example.examen.domain;

import java.time.LocalDate;

public class SpecialOffer extends Entity<Double>{
    private double specialOfferId;
    private double hotelId;
    private LocalDate startDate;
    private LocalDate endDate;
    private int percents;

    public SpecialOffer(double specialOfferId, double hotelId, LocalDate startDate, LocalDate endDate, int percents) {
        super(specialOfferId);
        this.specialOfferId = specialOfferId;
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public double getSpecialOfferId() {
        return specialOfferId;
    }

    public void setSpecialOfferId(double specialOfferId) {
        this.specialOfferId = specialOfferId;
    }

    public double getHotelId() {
        return hotelId;
    }

    public void setHotelId(double hotelId) {
        this.hotelId = hotelId;
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

    public int getPercents() {
        return percents;
    }

    public void setPercents(int percents) {
        this.percents = percents;
    }

    @Override
    public String toString() {
        return
                ";   startDate=" + startDate +
                ";   endDate=" + endDate +
                ";   percents=" + percents;
    }
}
