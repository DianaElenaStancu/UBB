package com.example.examen.repository;

import com.example.examen.config.ApplicationContext;
import com.example.examen.domain.Order;
import com.example.examen.domain.OrderItem;
import com.example.examen.domain.OrderStatus;
import com.example.examen.domain.exceptions.EntityAlreadyExistsException;
import com.example.examen.domain.exceptions.EntityMissingException;
import com.example.examen.domain.validators.ValidationException;
import com.example.examen.utils.observer.ConcreteObservable;
import com.example.examen.utils.observer.Observable;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class OrderTableDbRepository extends ConcreteObservable<Order> implements Repository<Integer, Order>{
    private final  String url;
    private final String username;
    private final String password;


    public OrderTableDbRepository() {
        this.url = ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl");
        this.username = ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername");
        this.password = ApplicationContext.getPROPERTIES().getProperty("data.databasePassword");
    }

    private Order extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
        Integer ordertableid = 0, tableid = 0, menuitemid = 0, quantity = 0;
        LocalDateTime date = LocalDateTime.now();
        OrderStatus status  = OrderStatus.PREPARING;
        List<OrderItem> orderItems = new ArrayList<>();
        while(resultSet.next()) {
            ordertableid = resultSet.getInt("ordertableid");
            menuitemid = resultSet.getInt("menuitemid");
            tableid = resultSet.getInt("tableid");
            quantity = resultSet.getInt("quantity");
            status = OrderStatus.valueOf(resultSet.getString("status"));
            date = resultSet.getTimestamp("date").toLocalDateTime();

            orderItems.add(new OrderItem(ordertableid, menuitemid, quantity));
        }

        return new Order(ordertableid, tableid, orderItems, date, status);
    }


    @Override
    public Order findOne(Integer ordertableid) throws IllegalArgumentException, EntityMissingException {
        if(ordertableid == null) {
            throw new IllegalArgumentException("Id must be not null!");
        }

        String sql = "select ot.id as id, ot.tableid as tableid, ot.date as date," +
                "ot.status as status, oi.ordertableid as ordertableid, " +
                "oi.menuitemid as menuitemid, oi.quantity as quantity" +
                " from ordertable ot inner join orderitems oi on oi.ordertableid = ot.id where oi.ordertableid=?";
        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setInt(1, ordertableid);
            ResultSet resultSet = statement.executeQuery();

            return extractEntityFromResultSet(resultSet);


        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return null;
    }

    @Override
    public Iterable<Order> findAll() {
        List<Order> orders = new ArrayList<>();
        String sql = "select id from ordertable";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while(resultSet.next()) {
                Integer order_id = resultSet.getInt("id");
                Order order = findOne(order_id);
                orders.add(order);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return orders;
    }

    @Override
    public Order save(Order order) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        //prima data adaugam in ordertable
        String sql = "insert into ordertable(tableid, date, status) values (?, ?, ?)";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, order.getTableId());
            preparedStatement.setTimestamp(2, Timestamp.valueOf(order.getDate()));
            preparedStatement.setString(3, order.getStatus().toString());
            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        //preluam id-ul acestui order
        Integer orderId = 0;
        String sql2 = "select id from ordertable order by id desc";
        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql2)) {

            ResultSet resultSet = statement.executeQuery();

            if(resultSet.next()) {
                orderId = resultSet.getInt("id");
            }
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        //adaugam in orderitems fiecare item
        Integer finalOrderId = orderId;
        order.getMenuItemList().forEach(orderItem -> {
            String sql3 = "insert into orderitems(menuitemid, quantity, ordertableid) values (?, ?, ?)";

            try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
                 PreparedStatement preparedStatement = connection.prepareStatement(sql3)) {
                preparedStatement.setInt(1, orderItem.getMenuItem()); //introducem id-ul produsului din meniu
                preparedStatement.setInt(2, orderItem.getQuantity());
                preparedStatement.setInt(3, finalOrderId);
                preparedStatement.executeUpdate();
            } catch (SQLException sqlException) {
                sqlException.printStackTrace();
            }
        });

        System.out.println("SALUT");
        this.notifyObservers(order);
        return order;
    }

    @Override
    public Order delete(Integer integer) throws IllegalArgumentException {
        return null;
    }

    @Override
    public Order update(Order order) throws IllegalArgumentException, ValidationException, EntityMissingException {
        findOne(order.getTableId());

        String sql = "update ordertable set status=? WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, order.getStatus().toString());
            preparedStatement.setInt(2, order.getId());


            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        notifyObservers(order);
        return order;
    }

    @Override
    public void clear() {
    }
}
