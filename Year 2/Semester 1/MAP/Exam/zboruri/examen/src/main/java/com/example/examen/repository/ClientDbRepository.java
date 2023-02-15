package com.example.examen.repository;

import com.example.examen.domain.Client;
import com.example.examen.domain.Hobbies;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ClientDbRepository extends AbstractRepository<Long, Client>{
    @Override
    protected Client getObjectFromResultSet(ResultSet resultSet) {
        Client entity = null;
        try {
            Long clientid = resultSet.getLong(1);
            String name = resultSet.getString(2);
            int fidelityGrade = resultSet.getInt(3);
            int varsta = resultSet.getInt(4);
            Hobbies hobbies = Hobbies.valueOf(resultSet.getString(5));

            entity = new Client(clientid, name, fidelityGrade, varsta, hobbies);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, Client entity) {
        try {
            ps.setLong(1, entity.getClientId());
            ps.setString(2, entity.getName());
            ps.setInt(3, entity.getFidelityGrade());
            ps.setInt(4, entity.getVarsta());
            ps.setString(5, entity.getHobbies().toString());

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from client where clientid = ";
        SELECT_ALL_SQL_STATEMENT = "select * from client";
        INSERT_SQL_STATEMENT = "insert into client values (?, ?, ?, ?, ?)";
        DELETE_SQL_STATEMENT = "delete from client where clientid = ";
        UPDATE_SQL_STATEMENT = "update client set clientid = ?, name = ?, " +
                "fidelitygrade=?, varsta=?, hobby=?  where clientid = ";
    }
}
