package com.example.examen.repository;

import com.example.examen.domain.Entity;
import com.example.examen.domain.Oras;
import com.example.examen.domain.Persoana;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PersoaneDbRepository extends AbstractRepository<Long, Persoana, Persoana>{
    @Override
    public void save(Persoana entity) {
        validate(entity);
        super.save(entity);
    }

    @Override
    protected Persoana getObjectFromResultSet(ResultSet resultSet) {
        Persoana entity = null;
        try {
            Long id = resultSet.getLong(1);
            String nume = resultSet.getString(2);
            String prenume = resultSet.getString(3);
            String username = resultSet.getString(4);
            String parola = resultSet.getString(5);
            Oras oras = Oras.valueOf(resultSet.getString(6));
            String strada = resultSet.getString(7);
            String numarstrada = resultSet.getString(8);
            String telefon = resultSet.getString(9);

            entity = new Persoana(id, nume, prenume, username, parola, oras, strada, numarstrada, telefon);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from persoane where id = ";
        SELECT_ALL_SQL_STATEMENT = "select * from persoane";
        INSERT_SQL_STATEMENT = "insert into persoane(nume, prenume, username, parola, oras, strada, numarstrada, telefon) values (?, ?, ?, ?, ?, ?, ?, ?)";
       // DELETE_SQL_STATEMENT = "delete from persoane where id = ";
        // UPDATE_SQL_STATEMENT = "update persoane set id = ?, nume where id = ";
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, Persoana entity) {
        try {
            ps.setString(1, entity.getNume());
            ps.setString(2, entity.getPrenume());
            ps.setString(3, entity.getUsername());
            ps.setString(4, entity.getParola());
            ps.setString(5, entity.getOras().toString());
            ps.setString(6, entity.getStrada());
            ps.setString(7, entity.getNumarStrada());
            ps.setString(8, entity.getTelefon());

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
