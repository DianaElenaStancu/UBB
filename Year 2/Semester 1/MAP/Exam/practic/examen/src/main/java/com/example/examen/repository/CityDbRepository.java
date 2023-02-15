package com.example.examen.repository;

import com.example.examen.domain.City;
import com.example.examen.domain.Entity;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CityDbRepository extends AbstractRepository<String, City>{
    @Override
    protected City getObjectFromResultSet(ResultSet resultSet) {
        City city;
        try {
            String id = resultSet.getString(1);
            String name = resultSet.getString(2);

            city = new City(id, name);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return city;
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from cities where id = ";
        SELECT_ALL_SQL_STATEMENT = "select * from cities";
    }


}
