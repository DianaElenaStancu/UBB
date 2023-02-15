package com.example.examen.repository;

import com.example.examen.config.ApplicationContext;
import com.example.examen.domain.Location;
import com.example.examen.domain.exceptions.EntityAlreadyExistsException;
import com.example.examen.domain.exceptions.EntityMissingException;
import com.example.examen.domain.validators.ValidationException;

import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class LocationDbRepository implements Repository<Double, Location>{
    private final  String url;
    private final String username;
    private final String password;

    public LocationDbRepository() {
        this.url = ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl");
        this.username = ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername");
        this.password = ApplicationContext.getPROPERTIES().getProperty("data.databasePassword");
    }


    @Override
    public Location findOne(Double aDouble) throws IllegalArgumentException, EntityMissingException {
        if (username == null) {
            throw new IllegalArgumentException("Username for the database is null!");
        }

        String sql = "select * from location where locationid = ?";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setDouble(1, aDouble);
            ResultSet resultSet = preparedStatement.executeQuery();

            if(!resultSet.next()) {
                throw new EntityMissingException(aDouble + " does not exist!");
            }

            return extractEntityFromResultSet(resultSet);

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return null;
    }


    private Location extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
        Double locationId = resultSet.getDouble("locationid");//Double.valueOf(resultSet.getFloat("locationid"));
        String locationName = resultSet.getString("locationname");

        return new Location(locationId, locationName);
    }

    @Override
    public Iterable<Location> findAll() {
        Set<Location> locations = new HashSet<>();
        String sql = "select * from location";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while(resultSet.next()) {
                Location location  = extractEntityFromResultSet(resultSet);
                locations.add(location);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return locations;
    }

    @Override
    public Location save(Location entity) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        return null;
    }

    @Override
    public Location delete(Double aDouble) throws IllegalArgumentException {
        return null;
    }

    @Override
    public Location update(Location entity) throws IllegalArgumentException, ValidationException, EntityMissingException {
        return null;
    }

    @Override
    public void clear() {

    }
}
