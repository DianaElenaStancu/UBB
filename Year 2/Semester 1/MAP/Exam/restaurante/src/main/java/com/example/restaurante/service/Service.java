package com.example.restaurante.service;

import com.example.restaurante.domain.*;
import com.example.restaurante.repository.Repository;
import com.example.restaurante.repository.database.OrdersDbRepository;
import com.example.restaurante.utils.observer.Observer;
import com.example.restaurante.utils.utils.OrderEvent;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Locale;

public class Service {
    private Repository<Integer, Table> tableRepository;
    private OrdersDbRepository orderRepository;
    private Repository<Integer, MenuItem> menuItemRepository;

    public Service(Repository<Integer, Table> tableRepository, Repository<Integer, Order> orderRepository, Repository<Integer, MenuItem> menuItemRepository) {
        this.tableRepository = tableRepository;
        this.orderRepository = (OrdersDbRepository) orderRepository;
        this.menuItemRepository = menuItemRepository;
    }

    public Iterable<Table> getAllTables() {
        return tableRepository.getAll();
    }


    public Iterable<Order> getAllOrders() {
        return orderRepository.getAll();
    }


    public Iterable<MenuItem> getAllMenuItems() {
        return menuItemRepository.getAll();
    }

    public void addOrderObservers(Observer<OrderEvent> observer) {
        orderRepository.addObserver(observer);
    }

    public void placeOrder(int table_id, List<OrderItem> orderItems) {
        Order order = new Order(0, new Table(table_id), LocalDateTime.now(), orderItems, OrderStatus.PLACED);
        orderRepository.add(order);
    }

    public void prepareOrder(int order_id, int table_id) {
        Order order = new Order(order_id, new Table(table_id), LocalDateTime.now(), null, OrderStatus.PREPARING);
        orderRepository.update(order);
    }

    public void deliverOrder(int order_id, int table_id) {
        Order order = new Order(order_id, new Table(table_id), LocalDateTime.now(), null, OrderStatus.SERVED);
        orderRepository.update(order);
    }
}
