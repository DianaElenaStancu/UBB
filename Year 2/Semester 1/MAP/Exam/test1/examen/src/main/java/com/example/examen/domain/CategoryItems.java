package com.example.examen.domain;

import java.util.List;

public class CategoryItems extends Entity<String>{
    private List<MenuItem> menuItems;


    public CategoryItems(String s, List<MenuItem> menuItems) {
        super(s);
        this.menuItems = menuItems;
    }

    public List<MenuItem> getMenuItems() {
        return menuItems;
    }

    @Override
    public String toString() {
        return getId() +
                "menuItems=" + menuItems +
                '\n';
    }
}

