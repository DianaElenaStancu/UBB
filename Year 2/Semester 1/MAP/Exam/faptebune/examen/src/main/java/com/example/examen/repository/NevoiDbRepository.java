package com.example.examen.repository;

import com.example.examen.domain.Nevoie;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;

public class NevoiDbRepository extends AbstractRepository<Long, Nevoie, Nevoie>{
    @Override
    protected Nevoie getObjectFromResultSet(ResultSet resultSet) {
        Nevoie entity = null;
        try {
            Long id = resultSet.getLong(1);
            String descriere = resultSet.getString(2);
            LocalDateTime deadline = resultSet.getTimestamp(3).toLocalDateTime();
            Long omInNevoie = resultSet.getLong(4);
            Long omSalvator = resultSet.getLong(5);
            String status = resultSet.getString(6);
            String titlu = resultSet.getString(7);


            entity = new Nevoie(id, titlu, descriere, deadline, omInNevoie, omSalvator, status);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    public void save(Nevoie entity) {
        super.save(entity);
        this.notifyObservers(entity);
    }

    @Override
    public void update(Nevoie entity) {
        super.update(entity);
        this.notifyObservers(entity);
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, Nevoie entity) {
        try {
            ps.setString(1, entity.getDescriere());
            ps.setTimestamp(2, Timestamp.valueOf(entity.getDeadline()));
            ps.setLong(3, entity.getOmInNevoie());
            ps.setLong(4, entity.getOmSalvator());
            ps.setString(5, entity.getStatus());
            ps.setString(6, entity.getTitlu());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from nevoie where id = ";
        SELECT_ALL_SQL_STATEMENT = "select * from nevoie";
        INSERT_SQL_STATEMENT = "insert into nevoie (descriere, deadline, ominnevoie, omsalvator, status, titlu)" +
                " values (?, ?, ?, ?, ?, ?)";
        DELETE_SQL_STATEMENT = "delete from nevoie where id = ";
        UPDATE_SQL_STATEMENT = "update nevoie set descriere=?, deadline=?, ominnevoie=?," +
                "omsalvator=?, status=?, titlu=? where id = ";
    }
}
