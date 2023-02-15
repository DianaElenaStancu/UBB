package com.example.examen.domain;

import java.time.LocalDateTime;

public class SpecialOffer extends Entity<Double>{
    private Double hotelId;
    private LocalDateTime startDate;
    private LocalDateTime endDate;
    private int percents;

    public SpecialOffer(Double specialOfferId, Double hotelId, LocalDateTime startDate, LocalDateTime endDate, int percents) {
        super(specialOfferId);
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public Double getHotelId() {
        return hotelId;
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDateTime startDate) {
        this.startDate = startDate;
    }

    public LocalDateTime getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDateTime endDate) {
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
        return "SpecialOffer{" +
                "hotelId=" + hotelId +
                ", startDate=" + startDate +
                ", endDate=" + endDate +
                ", percents=" + percents +
                '}';
    }
}
