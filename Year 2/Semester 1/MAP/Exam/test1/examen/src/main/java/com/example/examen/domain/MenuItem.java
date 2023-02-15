package com.example.examen.domain;

public class MenuItem extends Entity<Integer>{
    private String category;
    private String item;
    private float price;
    private String currency;

    public MenuItem(Integer integer, String category, String item, float price, String currency) {
        super(integer);
        this.category = category;
        this.item = item;
        this.price = price;
        this.currency = currency;
    }


    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getItem() {
        return item;
    }

    public void setItem(String item) {
        this.item = item;
    }

    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public String getCurrency() {
        return currency;
    }

    public void setCurrency(String currency) {
        this.currency = currency;
    }


    @Override
    public String toString() {
        return "MenuItem{" +
                "category='" + category + '\'' +
                ", item='" + item + '\'' +
                ", price=" + price +
                ", currency='" + currency + '\'' +
                '}';
    }
}
