package com.example.restaurante.controller;

import com.example.restaurante.domain.Order;
import com.example.restaurante.domain.OrderItem;
import com.example.restaurante.domain.OrderStatus;
import com.example.restaurante.service.Service;
import com.example.restaurante.utils.observer.ConcreteObservable;
import com.example.restaurante.utils.observer.Observer;
import com.example.restaurante.utils.utils.OrderEvent;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.Callback;

import java.util.List;

public class StaffController implements Observer<OrderEvent> {
    Service service;

    @FXML
    TableView<Order> placedOrdersTableView;
    ObservableList<Order> placedOrdersObservableList;
    @FXML
    TableView<Order> preparingOrdersTableView;
    ObservableList<Order> preparingOrdersObservableList;

    @FXML
    TableColumn prepareColumn;
    @FXML
    TableColumn deliverColumn;

    @FXML
    public void setService(Service service) {
        this.service = service;
        this.service.addOrderObservers(this);

        initPlacedOrdersTableView();
        updatePlacedOrdersTableView();
        initPreparingOrdersTableView();
        updatePreparingdOrdersTableView();
    }

    private void initPlacedOrdersTableView() {
        Callback<TableColumn<Order, String>, TableCell<Order, String>> cellFactory =
                new Callback<TableColumn<Order, String>, TableCell<Order, String>>() {
                    @Override
                    public TableCell call(final TableColumn<Order, String> param) {
                        final TableCell<Order, String> cell = new TableCell<Order, String>() {

                            final Button btn = new Button("Prepare");

                            @Override
                            public void updateItem(String item, boolean empty) {
                                super.updateItem(item, empty);
                                if (empty) {
                                    setGraphic(null);
                                    setText(null);
                                } else {
                                    btn.setOnAction(event -> {
                                        Order order = getTableView().getItems().get(getIndex());
                                        service.prepareOrder(order.getId(), order.getTableId());
                                    });
                                    setGraphic(btn);
                                    setText(null);
                                }
                            }
                        };
                        return cell;
                    }
                };
        prepareColumn.setCellFactory(cellFactory);
    }

    private void initPreparingOrdersTableView() {
        Callback<TableColumn<Order, String>, TableCell<Order, String>> cellFactory =
                new Callback<TableColumn<Order, String>, TableCell<Order, String>>() {
                    @Override
                    public TableCell call(final TableColumn<Order, String> param) {
                        final TableCell<Order, String> cell = new TableCell<Order, String>() {

                            final Button btn = new Button("Deliver");

                            @Override
                            public void updateItem(String item, boolean empty) {
                                super.updateItem(item, empty);
                                if (empty) {
                                    setGraphic(null);
                                    setText(null);
                                } else {
                                    btn.setOnAction(event -> {
                                        Order order = getTableView().getItems().get(getIndex());
                                        service.deliverOrder(order.getId(), order.getTableId());
                                    });
                                    setGraphic(btn);
                                    setText(null);
                                }
                            }
                        };
                        return cell;
                    }
                };
        deliverColumn.setCellFactory(cellFactory);
    }

    private void updatePlacedOrdersTableView() {
        List<Order> placedOrders = ((List<Order>)this.service.getAllOrders()).stream().filter(order -> order.getOrderStatus().equals(OrderStatus.PLACED)).toList();
        placedOrdersObservableList = FXCollections.observableArrayList(placedOrders);
        placedOrdersTableView.setItems(placedOrdersObservableList);
    }

    private void updatePreparingdOrdersTableView() {
        List<Order> preparingOrders = ((List<Order>)this.service.getAllOrders()).stream().filter(order -> order.getOrderStatus().equals(OrderStatus.PREPARING)).toList();
        preparingOrdersObservableList = FXCollections.observableArrayList(preparingOrders);
        preparingOrdersTableView.setItems(preparingOrdersObservableList);
    }

    @Override
    public void update(OrderEvent event) {
        updatePlacedOrdersTableView();
        updatePreparingdOrdersTableView();
    }
}
