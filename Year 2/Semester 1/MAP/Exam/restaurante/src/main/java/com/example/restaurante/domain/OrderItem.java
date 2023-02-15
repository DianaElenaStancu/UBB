package com.example.restaurante.domain;

import javafx.scene.control.Menu;

import java.util.Objects;

public class OrderItem {

    private MenuItem menuItem;
    private Integer quantity;

    public OrderItem(MenuItem menuItem, Integer quantity) {
        this.menuItem = menuItem;
        this.quantity = quantity;
    }

    public MenuItem getMenuItem() {
        return menuItem;
    }

    public void setMenuItem(MenuItem menuItem) {
        this.menuItem = menuItem;
    }

    public Integer getQuantity() {
        return quantity;
    }

    public void setQuantity(Integer quantity) {
        this.quantity = quantity;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof OrderItem orderItem)) return false;
        return menuItem.equals(orderItem.menuItem);
    }

    @Override
    public int hashCode() {
        return Objects.hash(menuItem);
    }
}
