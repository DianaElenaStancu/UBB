package com.example.examen.domain;

public class TrainStation extends Entity<String>{
    private String trainId;
    private String departureCityId;
    private String destinationCityId;

    public TrainStation(String trainId, String departureCityId, String destinationCityId) {
        super(trainId);
        this.trainId = trainId;
        this.departureCityId = departureCityId;
        this.destinationCityId = destinationCityId;
    }

    public String getTrainId() {
        return trainId;
    }

    public void setTrainId(String trainId) {
        this.trainId = trainId;
    }

    public String getDepartureCityId() {
        return departureCityId;
    }

    public void setDepartureCityId(String departureCityId) {
        this.departureCityId = departureCityId;
    }

    public String getDestinationCityId() {
        return destinationCityId;
    }

    public void setDestinationCityId(String destinationCityId) {
        this.destinationCityId = destinationCityId;
    }

    @Override
    public String toString() {
         return       "trainId='" + trainId + '\'' +
                ", departureCityId='" + departureCityId + '\'' +
                ", destinationCityId='" + destinationCityId + '\'';
    }
}
