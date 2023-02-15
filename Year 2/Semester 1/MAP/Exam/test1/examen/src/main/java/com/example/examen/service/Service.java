package com.example.examen.service;

import com.example.examen.controller.TableViewController;
import com.example.examen.domain.CategoryItems;
import com.example.examen.domain.MenuItem;
import com.example.examen.domain.Order;
import com.example.examen.domain.Table;
import com.example.examen.repository.Repository;
import com.example.examen.utils.observer.Observable;
import com.example.examen.utils.observer.Observer;

import java.util.*;
import java.util.stream.Collectors;

public class Service {
    private final Repository<Integer, Table> tableRepository;
    private final Repository<Integer, MenuItem> menuItemRepository;

    private final Repository<Integer, Order> orderRepository;
    //repo
    //validator
    //constructor
    //functions


    public Service(Repository<Integer, Table> tableRepository, Repository<Integer, MenuItem> menuItemRepository,
                   Repository<Integer, Order> orderRepository) {
        this.tableRepository = tableRepository;
        this.menuItemRepository = menuItemRepository;
        this.orderRepository = orderRepository;
    }


    public Iterable<Table> findAllTables() {
        return this.tableRepository.findAll();
    }

    public List<MenuItem> findAllMenuItems() {
        return new ArrayList<MenuItem>((Collection<MenuItem>) this.menuItemRepository.findAll());
    }

    public Iterable<String> getAllCategories() {
        List<MenuItem> menuItemList = (List)this.findAllMenuItems();
        return menuItemList.stream().map(MenuItem::getCategory).collect(Collectors.toSet());
    }


    public List<CategoryItems> getAllCategoryItems() {
        Set<String> categories = (Set)this.getAllCategories();
        List<CategoryItems> categoryItems = new ArrayList();
        categories.forEach(category -> {
            List<MenuItem> menuItemList = (List)this.findAllMenuItems();
            List<MenuItem> itemsFromCategory = menuItemList.stream().filter(menuItem -> menuItem.getCategory().equals(category)).toList();
            categoryItems.add(new CategoryItems(category, itemsFromCategory));
        });
        return categoryItems;
    }

    public Order getOrder(Integer ordertableid) {
        return orderRepository.findOne(ordertableid);
    }

    public Iterable<Order> getOrders() {
        return orderRepository.findAll();
    }


    public void saveOrder(Order order){
        orderRepository.save(order);
    }

    public void addOrderObservers(Observer observer) {
       Observable observable = (Observable)this.orderRepository;
       observable.addObserver(observer);
    }

    public void updateOrder(Order order) {
        this.orderRepository.update(order);
    }
}
