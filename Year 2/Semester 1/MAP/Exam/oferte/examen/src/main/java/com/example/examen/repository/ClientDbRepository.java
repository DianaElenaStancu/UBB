package com.example.examen.repository;

import com.example.examen.config.ApplicationContext;
import com.example.examen.domain.Client;
import com.example.examen.domain.Hobbies;
import com.example.examen.domain.Location;
import com.example.examen.domain.exceptions.EntityAlreadyExistsException;
import com.example.examen.domain.exceptions.EntityMissingException;
import com.example.examen.domain.validators.ValidationException;

import java.sql.*;

public class ClientDbRepository implements Repository<Long, Client>{
    private final  String url;
    private final String username;
    private final String password;

    public ClientDbRepository() {
        this.url = ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl");
        this.username = ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername");
        this.password = ApplicationContext.getPROPERTIES().getProperty("data.databasePassword");
    }

    private Client extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
        Long clientId = resultSet.getLong("clientid");
        String name = resultSet.getString("name");
        Integer fidelityGrade = resultSet.getInt("fidelitygrade");
        Integer varsta = resultSet.getInt("varsta");
        Hobbies hobby = Hobbies.valueOf(resultSet.getString("hobby"));

        return new Client(clientId, name, fidelityGrade, varsta, hobby);
    }
    @Override
    public Client findOne(Long clientId) throws IllegalArgumentException, EntityMissingException {
        if (username == null) {
            throw new IllegalArgumentException("Username for the database is null!");
        }

        String sql = "select * from client where clientid = ?";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setDouble(1, clientId);
            ResultSet resultSet = preparedStatement.executeQuery();

            if(!resultSet.next()) {
                throw new EntityMissingException(clientId + " does not exist!");
            }

            return extractEntityFromResultSet(resultSet);

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return null;
    }

    @Override
    public Iterable<Client> findAll() {
        return null;
    }

    @Override
    public Client save(Client entity) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        return null;
    }

    @Override
    public Client delete(Long aLong) throws IllegalArgumentException {
        return null;
    }

    @Override
    public Client update(Client entity) throws IllegalArgumentException, ValidationException, EntityMissingException {
        return null;
    }

    @Override
    public void clear() {

    }
}
