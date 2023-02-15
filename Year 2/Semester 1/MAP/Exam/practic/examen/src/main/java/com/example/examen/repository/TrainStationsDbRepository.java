package com.example.examen.repository;

import com.example.examen.domain.TrainStation;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class TrainStationsDbRepository extends AbstractRepository<String, TrainStation> {
    @Override
    protected TrainStation getObjectFromResultSet(ResultSet resultSet) {
        TrainStation trainstation;
        try {
            String trainId = resultSet.getString(1);
            String departureCityId = resultSet.getString(2);
            String destinationCityId = resultSet.getString(3);


            trainstation = new TrainStation(trainId, departureCityId, destinationCityId);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return trainstation;
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ALL_SQL_STATEMENT = "select * from trainstations";
    }
}
