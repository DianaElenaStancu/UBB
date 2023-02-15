package com.example.examen.domain;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;


public class Order extends Entity<Integer>{
    private int tableId;
    List<OrderItem> orderItemList;

    String orderItemListString;

    private LocalDateTime date;
    OrderStatus status;

    public Order(Integer integer, int table_id, List<OrderItem> menuItemList, LocalDateTime date, OrderStatus status) {
        super(integer);
        this.tableId = table_id;
        this.orderItemList = menuItemList;
        this.date = date;
        this.status = status;
    }

    public String getOrderItemListString() {
        return getOrderItemList().toString();
    }

    public List<OrderItem> getOrderItemList() {
        return orderItemList;
    }

    /*public List<String> getOrderItemListNames() {
        List<String> orderItemListNames = new ArrayList<String>();
        orderItemList.forEach(orderItem -> {
            orderItemListNames.add(orderItem.getMenuItem().getItem());
        });
    }*/
    public Order(int table_id, List<OrderItem> menuItemList, LocalDateTime date, OrderStatus status) {
        super(table_id);
        this.tableId = table_id;
        this.orderItemList = menuItemList;
        this.date = date;
        this.status = status;
    }

    public int getTableId() {
        return tableId;
    }

    public void setTableId(int tableId) {
        this.tableId = tableId;
    }

    public List<OrderItem> getMenuItemList() {
        return orderItemList;
    }

    public void setMenuItemList(List<OrderItem> menuItemList) {
        this.orderItemList = menuItemList;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "Order{" +
                "table_id=" + tableId +
                ", orderItemList=" + orderItemList +
                ", date=" + date +
                ", status=" + status +
                '}';
    }
}
