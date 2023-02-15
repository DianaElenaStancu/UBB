package com.example.examen.domain;

public class OrderItem extends Entity<Integer>{
    private int menuItem;
    private int quantity;

    public OrderItem(Integer integer, int menuItem, int quantity) {
        super(integer);
        this.menuItem = menuItem;
        this.quantity = quantity;
    }


    public int getMenuItem() {
        return menuItem;
    }

    public void setMenuItem(int menuItem) {
        this.menuItem = menuItem;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    @Override
    public String toString() {
        return "OrderItem{" +
                "menuItem=" + menuItem +
                ", quantity=" + quantity +
                '}';
    }
}
