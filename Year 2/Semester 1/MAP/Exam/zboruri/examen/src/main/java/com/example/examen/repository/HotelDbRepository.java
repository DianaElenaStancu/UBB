package com.example.examen.repository;

import com.example.examen.domain.Hotel;
import com.example.examen.domain.Location;
import com.example.examen.domain.Type;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class HotelDbRepository extends AbstractRepository<Double, Hotel>{

    @Override
    protected Hotel getObjectFromResultSet(ResultSet resultSet) {
        Hotel entity = null;
        try {
            Double hotelId = resultSet.getDouble(1);
            Double locationId = resultSet.getDouble(2);
            String hotelName = resultSet.getString(3);
            int noRooms = resultSet.getInt(4);
            Double pricePerNight = resultSet.getDouble(5);
            Type type = Type.valueOf(resultSet.getString(6));


            entity = new Hotel(hotelId, locationId, hotelName, noRooms, pricePerNight, type);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, Hotel entity) {
        try {
            ps.setDouble(1, entity.getHotelId());
            ps.setDouble(2, entity.getLocationId());
            ps.setString(3, entity.getHotelName());
            ps.setInt(4, entity.getNoRooms());
            ps.setDouble(5, entity.getPricePerNight());
            ps.setString(6, entity.getType().toString());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from hotel where hotelid = ";
        SELECT_ALL_SQL_STATEMENT = "select * from hotel";
        INSERT_SQL_STATEMENT = "insert into hotel values (?, ?, ?, ?, ?, ?)";
        DELETE_SQL_STATEMENT = "delete from hotel where hotelid = ";
        UPDATE_SQL_STATEMENT = "update location set hotelid = ?, locationid = ?, " +
                "hotelname=?, notrooms=?, pricepernight=?, type=? where hotelid = ";

    }
}
