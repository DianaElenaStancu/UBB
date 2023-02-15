package com.example.examen.repository;

import com.example.examen.domain.Hotel;
import com.example.examen.domain.SpecialOffer;
import com.example.examen.domain.Type;

import java.sql.*;
import java.time.LocalDate;

public class SpecialOfferDbRepository extends AbstractRepository<Double, SpecialOffer> {
    @Override
    protected SpecialOffer getObjectFromResultSet(ResultSet resultSet) {
        SpecialOffer entity = null;
        try {
            Double specialOfferId = resultSet.getDouble(1);
            Double hotelId = resultSet.getDouble(2);
            LocalDate startDate = resultSet.getDate(3).toLocalDate();
            LocalDate endDate = resultSet.getDate(4).toLocalDate();
            int percents = resultSet.getInt(5);


            entity = new SpecialOffer(specialOfferId, hotelId, startDate, endDate, percents);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, SpecialOffer entity) {
        try {
            ps.setDouble(1, entity.getSpecialOfferId());
            ps.setDouble(2, entity.getHotelId());
            ps.setDate(3, Date.valueOf(entity.getStartDate()));
            ps.setDate(4, Date.valueOf(entity.getEndDate()));
            ps.setInt(5, entity.getPercents());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from specialoffers where specialofferid = ";
        SELECT_ALL_SQL_STATEMENT = "select * from specialoffers";
        INSERT_SQL_STATEMENT = "insert into specialoffers values (?, ?, ?, ?, ?)";
        DELETE_SQL_STATEMENT = "delete from specialoffers where specialofferid = ";
        UPDATE_SQL_STATEMENT = "update location set specialofferid = ?, hotelid = ?, " +
                "startdate=?, enddate=?, percents=? where specialofferid = ";


    }
}
