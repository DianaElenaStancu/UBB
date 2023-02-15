package com.example.examen.repository;

import com.example.examen.config.ApplicationContext;
import com.example.examen.domain.Location;
import com.example.examen.domain.SpecialOffer;
import com.example.examen.domain.Type;
import com.example.examen.domain.exceptions.EntityAlreadyExistsException;
import com.example.examen.domain.exceptions.EntityMissingException;
import com.example.examen.domain.validators.ValidationException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Set;

public class SpecialOfferDbRepository implements Repository<Double, SpecialOffer> {
    private final  String url;
    private final String username;
    private final String password;

    public SpecialOfferDbRepository() {
        this.url = ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl");
        this.username = ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername");
        this.password = ApplicationContext.getPROPERTIES().getProperty("data.databasePassword");
    }

    @Override
    public SpecialOffer findOne(Double aDouble) throws IllegalArgumentException, EntityMissingException {
        return null;
    }

    private SpecialOffer extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
        Double speciaOfferId = resultSet.getDouble("specialofferid");
        Double hotelId = resultSet.getDouble("hotelid");//Double.valueOf(resultSet.getFloat("hotelid"));
        LocalDateTime startDate = resultSet.getTimestamp("startdate").toLocalDateTime();
        LocalDateTime endDate = resultSet.getTimestamp("enddate").toLocalDateTime();
        int percent = resultSet.getInt("percents");
        return new SpecialOffer(speciaOfferId, hotelId, startDate, endDate, percent);
    }

    @Override
    public Iterable<SpecialOffer> findAll() {
        Set<SpecialOffer> specialoffers = new HashSet<>();
        String sql = "select * from specialoffers";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while(resultSet.next()) {
                SpecialOffer specialoffer  = extractEntityFromResultSet(resultSet);
                specialoffers.add(specialoffer);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return specialoffers;
    }

    @Override
    public SpecialOffer save(SpecialOffer entity) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        return null;
    }

    @Override
    public SpecialOffer delete(Double aDouble) throws IllegalArgumentException {
        return null;
    }

    @Override
    public SpecialOffer update(SpecialOffer entity) throws IllegalArgumentException, ValidationException, EntityMissingException {
        return null;
    }

    @Override
    public void clear() {

    }
}
