package com.example.examen.domain;

import java.time.LocalDateTime;

public class Reservation extends Entity<Double>{
    private double reservationId;
    private double clientId;
    private double hotelId;
    private LocalDateTime startDate;
    private int noNights;

    public Reservation(double reservationId, double clientId, double hotelId, LocalDateTime startDate, int noNights) {
        super(reservationId);
        this.reservationId = reservationId;
        this.clientId = clientId;
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.noNights = noNights;
    }

    public double getReservationId() {
        return reservationId;
    }

    public void setReservationId(double reservationId) {
        this.reservationId = reservationId;
    }

    public double getClientId() {
        return clientId;
    }

    public void setClientId(double clientId) {
        this.clientId = clientId;
    }

    public double getHotelId() {
        return hotelId;
    }

    public void setHotelId(double hotelId) {
        this.hotelId = hotelId;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDateTime startDate) {
        this.startDate = startDate;
    }

    public int getNoNights() {
        return noNights;
    }

    public void setNoNights(int noNights) {
        this.noNights = noNights;
    }

    @Override
    public String toString() {
        return "Reservation{" +
                "reservationId=" + reservationId +
                ", clientId=" + clientId +
                ", hotelId=" + hotelId +
                ", startDate=" + startDate +
                ", noNights=" + noNights +
                '}';
    }
}
