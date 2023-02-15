package com.example.examen.repository;

import com.example.examen.config.ApplicationContext;
import com.example.examen.domain.Hotel;
import com.example.examen.domain.Location;
import com.example.examen.domain.Type;
import com.example.examen.domain.exceptions.EntityAlreadyExistsException;
import com.example.examen.domain.exceptions.EntityMissingException;
import com.example.examen.domain.validators.ValidationException;

import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class HotelDbRepository implements Repository<Double, Hotel> {

    private final  String url;
    private final String username;
    private final String password;

    public HotelDbRepository() {
        this.url = ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl");
        this.username = ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername");
        this.password = ApplicationContext.getPROPERTIES().getProperty("data.databasePassword");
    }

    @Override
    public Hotel findOne(Double aDouble) throws IllegalArgumentException, EntityMissingException {
        return null;
    }

    @Override
    public Iterable<Hotel> findAll() {
        Set<Hotel> hotels = new HashSet<>();
        String sql = "select * from hotel";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while(resultSet.next()) {
                Hotel hotel  = extractEntityFromResultSet(resultSet);
                hotels.add(hotel);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return hotels;
    }

    private Hotel extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
        Double hotelId = resultSet.getDouble("hotelid");//Double.valueOf(resultSet.getFloat("hotelid"));
        Double locationId = resultSet.getDouble("locationid");//Double.valueOf(resultSet.getFloat("locationid"));
        String hotelName = resultSet.getString("hotelname");
        int noRooms = resultSet.getInt("norooms");
        Double pricePerNight = resultSet.getDouble("pricepernight");//Double.valueOf(resultSet.getFloat("pricepernight"));
        Type type = Type.valueOf(resultSet.getString("type"));

        return new Hotel(hotelId, locationId, hotelName, noRooms, pricePerNight, type);
    }

    @Override
    public Hotel save(Hotel entity) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        return null;
    }

    @Override
    public Hotel delete(Double aDouble) throws IllegalArgumentException {
        return null;
    }

    @Override
    public Hotel update(Hotel entity) throws IllegalArgumentException, ValidationException, EntityMissingException {
        return null;
    }

    @Override
    public void clear() {

    }
}
