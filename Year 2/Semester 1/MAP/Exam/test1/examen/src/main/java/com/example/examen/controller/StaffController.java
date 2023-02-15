package com.example.examen.controller;

import com.example.examen.domain.Order;
import com.example.examen.domain.OrderStatus;
import com.example.examen.domain.Table;
import com.example.examen.service.Service;
import com.example.examen.utils.Event;
import com.example.examen.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.LocalDateTime;
import java.util.List;

public class StaffController extends AbstractController implements Observer<Order> {

    Service service;
    ObservableList<Order> placedOrders = FXCollections.observableArrayList();
    ObservableList<Order> preparedOrders = FXCollections.observableArrayList();

    @FXML
    TableView tableViewPreparedId, tableViewPlacedId;

    @FXML
    TableColumn<Order, Integer> masaPreparedId;

    @FXML
    TableColumn<Order, Integer> masaPlacedId;
    @FXML
    TableColumn<Order, String>  produsePreparedId, produsePlacedId;
    @FXML
    TableColumn<Order, LocalDateTime> dataPreparedId, dataPlacedId;

    @FXML
    Button placeButtonId, PrepareButtonId;

    @Override
    public void setTable(Table table) {

    }

    public void setService(Service service) {
        this.service = service;
        this.service.addOrderObservers(this);
        setPreparedOrders();
        setPlacedOrders();
    }

    private void setPlacedOrders() {
        placedOrders.clear();
        Iterable<Order> orders = service.getOrders();
        orders.forEach(order -> {if(order.getStatus() == OrderStatus.PREPARING) placedOrders.add(order);});
    }

    private void setPreparedOrders() {
        preparedOrders.clear();
        Iterable<Order> orders = service.getOrders();
        orders.forEach(order -> {if(order.getStatus() == OrderStatus.PLACED) preparedOrders.add(order);});
    }

    @FXML
    public void initialize() {
        masaPreparedId.setCellValueFactory(new PropertyValueFactory<>("tableId"));
        produsePreparedId.setCellValueFactory(new PropertyValueFactory<>("orderItemListString"));
        dataPreparedId.setCellValueFactory(new PropertyValueFactory<>("date"));

        masaPlacedId.setCellValueFactory(new PropertyValueFactory<>("tableId"));
        produsePlacedId.setCellValueFactory(new PropertyValueFactory<>("orderItemListString"));
        dataPlacedId.setCellValueFactory(new PropertyValueFactory<>("date"));

        tableViewPreparedId.setItems(preparedOrders);
        tableViewPlacedId.setItems(placedOrders);
    }

    private void updatePlacedOrdersTableView() {
        setPlacedOrders();
        tableViewPlacedId.setItems(placedOrders);
    }

    private void updatePreparingdOrdersTableView() {
        setPreparedOrders();
        tableViewPreparedId.setItems(preparedOrders);
    }
    @Override
    public void update(Order event) {
        updatePlacedOrdersTableView();
        updatePreparingdOrdersTableView();
    }

    public void preparedButtonOnAction(){
        Order order = (Order) tableViewPreparedId.getSelectionModel().getSelectedItem();
        if (order != null) {
            order.setStatus(OrderStatus.PREPARING);
            try {
                this.service.updateOrder(order);
            } catch(Exception exception) {
                MessageAlert.showErrorMessage((Stage)(tableViewPreparedId.getScene().getWindow()), "Eroare");
            }
        }
        update(order);
    }

    public void deliveredButtonOnAction() {
        Order order = (Order) tableViewPlacedId.getSelectionModel().getSelectedItem();
        if (order != null) {
            order.setStatus(OrderStatus.SERVED);
            try {
                this.service.updateOrder(order);
            } catch(Exception exception) {
                MessageAlert.showErrorMessage((Stage)(tableViewPreparedId.getScene().getWindow()), "Eroare");
            }
        }
        update(order);
    }
}
