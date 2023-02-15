package com.example.examen.repository;

import com.example.examen.domain.Location;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LocationDbRepository extends AbstractRepository<Double, Location>{
    @Override
    protected Location getObjectFromResultSet(ResultSet resultSet) {
        Location entity = null;
        try {
            Double id = resultSet.getDouble(1);
            String name = resultSet.getString(2);

            entity = new Location(id, name);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, Location entity) {
        try {
            ps.setDouble(1, entity.getLocationId());
            ps.setString(2, entity.getLocationName());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from location where locationid = ";
        SELECT_ALL_SQL_STATEMENT = "select * from location";
        INSERT_SQL_STATEMENT = "insert into location (locationid, locationname) values (?, ?)";
        DELETE_SQL_STATEMENT = "delete from location where locationid = ";
        UPDATE_SQL_STATEMENT = "update location set locationid = ?, locationname = ? where locationid = ";
    }
}
