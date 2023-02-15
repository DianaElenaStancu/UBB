package com.example.examen.repository;

import com.example.examen.domain.Entity;
import com.example.examen.domain.validators.Validator;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public abstract class AbstractRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private static final String URL = "jdbc:postgresql://localhost:5432/examen";
    private static final String USER = "postgres";
    private static final String PASSWORD = "parola";
    protected String SELECT_ONE_SQL_STATEMENT = null;
    protected String SELECT_ALL_SQL_STATEMENT = null;
    protected String INSERT_SQL_STATEMENT = null;
    protected String DELETE_SQL_STATEMENT = null;
    protected String UPDATE_SQL_STATEMENT = null;
    private Validator<E> validator = null;

    protected abstract E getObjectFromResultSet(ResultSet resultSet);

    protected abstract void setParametersForPreparedStatement(PreparedStatement ps, E entity);

    protected abstract void setSqlStatements();

    public void setValidator(Validator<E> validator) {
        this.validator = validator;
    }

    public AbstractRepository() {
        setSqlStatements();
    }

    @Override
    public E findOne(ID id) {
        if (SELECT_ONE_SQL_STATEMENT == null)
            throw new RuntimeException("NOT IMPLEMENTED");

        if (id == null)
            throw new IllegalArgumentException();

        String sql = SELECT_ONE_SQL_STATEMENT + id;

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(sql);
             ResultSet resultSet = statement.executeQuery()) {
            if (resultSet.next())
                return getObjectFromResultSet(resultSet);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return null;
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

    @Override
    public void save(E entity) {
        if (INSERT_SQL_STATEMENT == null)
            throw new RuntimeException("NOT IMPLEMENTED");

        if (entity == null)
            throw new IllegalArgumentException();

        String sql = INSERT_SQL_STATEMENT;

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            setParametersForPreparedStatement(ps, entity);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void update(E entity) {
        if (UPDATE_SQL_STATEMENT == null)
            throw new RuntimeException("NOT IMPLEMENTED");

        if (entity == null)
            throw new IllegalArgumentException();

        String sql = UPDATE_SQL_STATEMENT + entity.getId();

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            setParametersForPreparedStatement(preparedStatement, entity);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void delete(ID id) {
        if (DELETE_SQL_STATEMENT == null)
            throw new RuntimeException("NOT IMPLEMENTED");

        if (id == null)
            throw new IllegalArgumentException();
        String sql = DELETE_SQL_STATEMENT + id;

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(sql);) {
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void validate(E entity) {
        if(validator == null)
            return;
        validator.validate(entity);
    }
}

