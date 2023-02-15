package com.example.examen.controller;

import com.example.examen.domain.*;
import com.example.examen.service.Service;
import com.example.examen.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class TableViewController extends AbstractController implements Observer<Order> {
    private Service service;
    private Table table;

    List<OrderItem> orderMenuItems = new ArrayList<>();
    @FXML
    ListView menuListViewId;

    @FXML
    Button comandaButtonId;

    @FXML
    ObservableList<CategoryItems>  menuObservableList;


    public void setTable(Table table){this.table = table;}
    @Override
    public void setService(Service service) {
        this.service = service;
        this.service.addOrderObservers(this);
        initMenu();
    }

    private void initMenu() {
        //menuListViewId.setCellFactory();
        menuListViewId.setCellFactory(cell -> new CategoryItemsCell(table, orderMenuItems, comandaButtonId));
        menuObservableList = FXCollections.observableArrayList();
        menuObservableList.addAll(service.getAllCategoryItems());
        //menuObservableList = (ObservableList<CategoryItems>) service.getAllCategoryItems();
        menuListViewId.setItems(menuObservableList);
    }

    @FXML
    public void initialize() {};

    public void comandaOnAction(ActionEvent actionEvent) {
        this.service.saveOrder(new Order(table.getId(), orderMenuItems, LocalDateTime.now(), OrderStatus.PLACED));
    }

    @Override
    public void update(Order order) {
        System.out.println(order.getTableId());
        System.out.println(table.getId().toString());
        if(order.getTableId() == table.getId()){
            //MessageAlert.showErrorMessage((Stage)(comandaButtonId.getScene().getWindow()), "Your command is " + order.getStatus().toString());
            showInformationAlert(table.getId().toString(), "notificare comanda", "Your command is " + order.getStatus().toString());
        }
    }
}
