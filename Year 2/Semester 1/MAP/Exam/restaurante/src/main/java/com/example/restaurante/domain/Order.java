package com.example.restaurante.domain;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Objects;

public class Order extends Entity<Integer> {
    private Table table;
    private LocalDateTime date;
    private List<OrderItem> orderItems;
    OrderStatus orderStatus;

    public Order(int id, Table table, LocalDateTime date, List<OrderItem> orderItems, OrderStatus orderStatus) {
        super(id);
        this.table = table;
        this.date = date;
        this.orderItems = orderItems;
        this.orderStatus = orderStatus;
    }

    public Order(int id, Table table, List<OrderItem> orderItems, OrderStatus orderStatus) {
        super(id);
        this.table = table;
        this.date = LocalDateTime.now();
        this.orderItems = orderItems;
        this.orderStatus = orderStatus;
    }

    public Integer getTableId() {
        return table.getId();
    }

    public Table getTable() {
        return table;
    }

    public void setTable(Table table) {
        this.table = table;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public List<OrderItem> getOrderItems() {
        return orderItems;
    }

    public void setOrderItems(List<OrderItem> orderItems) {
        this.orderItems = orderItems;
    }

    public void addOrderItem(OrderItem orderItem) {
        this.orderItems.add(orderItem);
    }

    public OrderStatus getOrderStatus() {
        return orderStatus;
    }

    public void setOrderStatus(OrderStatus orderStatus) {
        this.orderStatus = orderStatus;
    }

    public String getItemsOrder() {
        return this.orderItems.stream()
                .map(orderItem -> orderItem.getMenuItem().getItem() + " - " + orderItem.getQuantity().toString() + "\n")
                .reduce("", (x, y) -> x + y);
    }
}
