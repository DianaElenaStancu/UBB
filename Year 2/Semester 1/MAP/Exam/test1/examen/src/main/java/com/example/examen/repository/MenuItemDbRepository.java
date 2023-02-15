package com.example.examen.repository;

import com.example.examen.config.ApplicationContext;
import com.example.examen.domain.MenuItem;
import com.example.examen.domain.exceptions.EntityAlreadyExistsException;
import com.example.examen.domain.exceptions.EntityMissingException;
import com.example.examen.domain.validators.ValidationException;

import java.sql.*;
import java.util.HashSet;
import java.util.Set;

import java.lang.UnsupportedOperationException;

public class MenuItemDbRepository implements Repository<Integer, MenuItem>{
    private final  String url;
    private final String username;
    private final String password;

    /**
     * creates a table repository
     * @param url of the database
     * @param password for connecting to the database
     * @param username for connecting to the database
     */
    public MenuItemDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    public MenuItemDbRepository() {
        this.url = ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl");
        this.username = ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername");
        this.password = ApplicationContext.getPROPERTIES().getProperty("data.databasePassword");
    }

    /**
     * extracts a table form a resultSet
     * @param resultSet - result of a query
     * @return the MenuItem from the resultSet
     * @throws SQLException if the result cannot be converted to entity
     */
    private MenuItem extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
        Integer id = resultSet.getInt("id");
        String category = resultSet.getString("category");
        String item = resultSet.getString("item");
        String currency = resultSet.getString("currency");
        float price = resultSet.getFloat("price");

        return new MenuItem(id, category, item, price, currency);
    }

    /**
     * Searches for a table
     * @param tableid the id of the entity to be returned
     *           id must not be null
     * @return MenuItem the table that was found
     * @throws IllegalArgumentException if the tablename is null
     * @throws EntityMissingException if the table doesn't exist
     */
    @Override
    public MenuItem findOne(Integer tableid) throws IllegalArgumentException, EntityMissingException {
        if (tableid == null) {
            throw new IllegalArgumentException("MenuItemid for the database is null!");
        }

        String sql = "select * from menuitem where id = ?";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, tableid.toString());
            ResultSet resultSet = preparedStatement.executeQuery();

            if(!resultSet.next()) {
                throw new EntityMissingException(tableid + " does not exist!");
            }

            return extractEntityFromResultSet(resultSet);

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return null;
    }

    /**
     * Creates an Iterable<MenuItem> with all tables from the database
     * @return Iterable<MenuItem>
     */
    @Override
    public Iterable<MenuItem> findAll() {
        Set<MenuItem> tables = new HashSet<>();
        String sql = "select * from menuitem";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while(resultSet.next()) {
                MenuItem table  = extractEntityFromResultSet(resultSet);
                tables.add(table);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return tables;
    }

    private boolean tableExists(Integer tableid) {
        try {
            findOne(tableid);
        } catch (EntityMissingException e) {
            return false;
        }
        return true;
    }

    /**
     * Saves a new table into database
     * @param table
     *         entity must be not null
     * @return table that was added
     * @throws ValidationException if the table is not valid
     * @throws IllegalArgumentException .
     * @throws EntityAlreadyExistsException if the entity is already in the database
     */
    @Override
    public MenuItem save(MenuItem table) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        throw new UnsupportedOperationException();
    }

    /**
     * Deletes a table from the database
     * @param tableid
     *      id must be not null
     * @return table with the given tableid
     * @throws IllegalArgumentException .
     */
    @Override
    public MenuItem delete(Integer tableid) throws IllegalArgumentException, UnsupportedOperationException {
        throw new UnsupportedOperationException();
    }


    /**
     * updates a table from the database
     * @param table
     *          entity must not be null
     * @return MenuItem the table updated
     * @throws IllegalArgumentException .
     * @throws ValidationException .
     * @throws EntityMissingException if the table that wants to be updated is not in the database.
     */
    @Override
    public MenuItem update(MenuItem table) throws IllegalArgumentException, ValidationException, EntityMissingException {
        throw new UnsupportedOperationException();
    }

    @Override
    public void clear() {
        throw new UnsupportedOperationException();
    }
}
