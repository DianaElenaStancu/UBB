package com.example.examen.repository;

import com.example.examen.domain.Reservation;
import com.example.examen.utils.observer.ConcreteObservable;
import com.example.examen.utils.observer.Observable;
import com.example.examen.utils.observer.Observer;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class ReservationDbRepository extends AbstractRepository<Double, Reservation> implements Observable<Reservation> {
    private Set<Observer<Reservation>> observers = new HashSet<>();
    //private List<Observer<Reservation>> observers = new ArrayList<>();
    @Override
    protected Reservation getObjectFromResultSet(ResultSet resultSet) {
        Reservation entity = null;
        try {
            Double id = resultSet.getDouble(1);
            Double clientid = resultSet.getDouble(2);
            Double hotelid = resultSet.getDouble(3);
            LocalDateTime startdate = resultSet.getTimestamp(4).toLocalDateTime();
            int nonights = resultSet.getInt(5);
            entity = new Reservation(id, clientid, hotelid, startdate, nonights);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    public void save(Reservation entity) {
        super.save(entity);
        System.out.println(observers);
        notifyObservers(entity);
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, Reservation entity) {
        try {
            ps.setDouble(1, entity.getId());
            ps.setDouble(2, entity.getClientId());
            ps.setDouble(3, entity.getHotelId());
            ps.setTimestamp(4, Timestamp.valueOf(entity.getStartDate()));
            ps.setInt(5, entity.getNoNights());


        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from reservation where id = ";
        SELECT_ALL_SQL_STATEMENT = "select * from reservation";
        INSERT_SQL_STATEMENT = "insert into reservation values (?, ?, ?, ?, ?)";
        DELETE_SQL_STATEMENT = "delete from reservation where id = ";
        UPDATE_SQL_STATEMENT = "update reservation set id = ?, clientid = ?, hotelid=?, startdate=?, nonights=? where id = ";
    }

    @Override
    public void addObserver(Observer<Reservation> observer) {

        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<Reservation> observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(Reservation event) {
        observers.forEach(observer -> observer.update(event));
    }
}
