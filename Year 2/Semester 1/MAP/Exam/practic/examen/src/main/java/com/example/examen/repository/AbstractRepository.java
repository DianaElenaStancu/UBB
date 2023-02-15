package com.example.examen.repository;

import com.example.examen.domain.Entity;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
public abstract class AbstractRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private static final String URL = "jdbc:postgresql://localhost:5432/examen";
    private static final String USER = "postgres";
    private static final String PASSWORD = "parola";
    protected String SELECT_ONE_SQL_STATEMENT = null;
    protected String SELECT_ALL_SQL_STATEMENT = null;

    protected abstract E getObjectFromResultSet(ResultSet resultSet);


    protected abstract void setSqlStatements();

    public AbstractRepository() {
        setSqlStatements();
    }


    @Override
    public Iterable<E> findAll() {
        if (SELECT_ALL_SQL_STATEMENT == null)
            throw new RuntimeException("NOT IMPLEMENTED");

        String sql = SELECT_ALL_SQL_STATEMENT;

        List<E> objects = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(sql);
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                objects.add(getObjectFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return objects;
    }
}

