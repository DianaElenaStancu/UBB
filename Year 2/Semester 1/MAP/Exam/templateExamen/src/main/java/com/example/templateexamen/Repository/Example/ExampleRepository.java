package com.example.templateexamen.Repository.Example;

import com.example.templateexamen.Domain.Example.ExampleEntity;
import com.example.templateexamen.Repository.AbstractRepository;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ExampleRepository extends AbstractRepository<Integer, ExampleEntity> {
    @Override
    protected ExampleEntity getObjectFromResultSet(ResultSet resultSet) {
        ExampleEntity entity = null;
        try {
            Integer id = resultSet.getInt(1);
            String name = resultSet.getString(2);

            entity = new ExampleEntity(id, name);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return entity;
    }

    @Override
    protected void setParametersForPreparedStatement(PreparedStatement ps, ExampleEntity entity) {
        try {
            ps.setInt(1, entity.getId());
            ps.setString(2, entity.getName());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void setSqlStatements() {
        SELECT_ONE_SQL_STATEMENT = "select * from ent where id = ";
        SELECT_ALL_SQL_STATEMENT = "select * from ent";
        INSERT_SQL_STATEMENT = "insert into ent (id, name) values (?, ?)";
        DELETE_SQL_STATEMENT = "delete from ent where id = ";
        UPDATE_SQL_STATEMENT = "update ent set id = ?, name = ? where id = ";
    }
}

/*
Repository<Integer, ExampleEntity> repository = new ExampleRepository();
repository.save(new ExampleEntity(1, "Andrei"));
repository.save(new ExampleEntity(2, "Andrei2"));
repository.save(new ExampleEntity(3, "Andrei3"));

repository.delete(1);
System.out.println(repository.findAll());

repository.update(new ExampleEntity(2, "Andrei22"));
System.out.println(repository.findOne(2));
 */