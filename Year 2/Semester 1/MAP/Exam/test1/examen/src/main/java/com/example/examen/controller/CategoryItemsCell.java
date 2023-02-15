package com.example.examen.controller;

import com.example.examen.domain.CategoryItems;
import com.example.examen.domain.MenuItem;

import com.example.examen.domain.OrderItem;
import com.example.examen.domain.Table;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import java.util.List;

public class CategoryItemsCell extends ListCell<CategoryItems> {
    @FXML
    private VBox categoryBox = new VBox();
    @FXML
    private Label categoryLabel = new Label();
    @FXML
    private ListView<MenuItem> menuItemListView = new ListView<>();
    @FXML
    private ObservableList<MenuItem> itemsObservableList = FXCollections.observableArrayList();


    public CategoryItemsCell(Table table, List<OrderItem> orderItemList, Button comandaButtonid) {
        categoryBox.getChildren().setAll(categoryLabel, menuItemListView);
        createMenuItemListView(table, orderItemList, comandaButtonid);
    }

    @Override
    protected void updateItem(CategoryItems categoryItems, boolean empty) {
        super.updateItem(categoryItems, empty);
        setText(null);
        if (empty) {
            setGraphic(null);
        } else {
            categoryLabel.setText(categoryItems.getId());
            itemsObservableList.setAll(categoryItems.getMenuItems());
            setGraphic(categoryBox);
        }
    }

    private void createMenuItemListView(Table table, List<OrderItem> orderItemList, Button comandaButtonid){
        menuItemListView.setCellFactory(list -> new ListCell<MenuItem>() {
            private HBox itemBox = new HBox();
            private Label nameLabel = new Label();
            private Label priceLabel = new Label();
            private Pane pane1 = new Pane();
            private Pane pane2 = new Pane();
            private Pane pane3 = new Pane();

            private CheckBox checkBox = new CheckBox();
            private TextField quantityField = new TextField();

            @Override
            protected void updateItem(MenuItem menuItem, boolean empty) {
                super.updateItem(menuItem, empty);
                if (empty) {
                    setGraphic(null);
                } else {

                    //adaugam listener
                    checkBox.disableProperty().setValue(true);
                    checkBox.selectedProperty().addListener(listener -> {
                        if(checkBox.isSelected()) {
                            try{
                                orderItemList.add(new OrderItem(table.getId(), menuItem.getId(), Integer.parseInt(quantityField.getText())));
                            } catch(Exception exception) {
                                MessageAlert.showErrorMessage((Stage)(checkBox.getScene().getWindow()), "Eroare valoare cantitate");
                                checkBox.selectedProperty().setValue(false);
                            }
                            if(comandaButtonid.disableProperty().get()) {
                                comandaButtonid.setDisable(false);
                            }
                        } else {
                            orderItemList.remove(new OrderItem(table.getId(), menuItem.getId(), Integer.parseInt(quantityField.getText())));
                            if(orderItemList.isEmpty()) {
                                comandaButtonid.setDisable(true);
                            }
                        }
                    });

                    quantityField.textProperty().addListener((listener, oldValue, newValue) -> {
                        if(quantityField.getText().isEmpty()) {
                            checkBox.disableProperty().setValue(true);
                            checkBox.selectedProperty().setValue(false);
                            orderItemList.remove(new OrderItem(table.getId(), menuItem.getId(), 0));//pt ce?
                            return;
                        } else {
                            checkBox.disableProperty().setValue(false);
                        }
                        if(checkBox.isSelected()) {
                            try{
                                orderItemList.remove(new OrderItem(table.getId(), menuItem.getId(), 0));
                                orderItemList.add(new OrderItem(table.getId(), menuItem.getId(), Integer.parseInt(quantityField.getText())));
                            } catch (NumberFormatException numberFormatException) {
                                MessageAlert.showErrorMessage((Stage)(checkBox.getScene().getWindow()), "Eroare valoare cantitate");
                            }
                        }
                    });

                    quantityField.setStyle("-fx-pref-width: 50");
                    itemBox.getChildren().setAll(checkBox, pane1, nameLabel, pane2, priceLabel, pane3, quantityField);
                    HBox.setHgrow(pane1, Priority.ALWAYS);
                    HBox.setHgrow(pane2, Priority.ALWAYS);
                    HBox.setHgrow(pane3, Priority.ALWAYS);
                    nameLabel.setText(menuItem.getItem());
                    priceLabel.setText(menuItem.getPrice() + " " + menuItem.getCurrency());
                    setGraphic(itemBox);
                }
            }
        });
        menuItemListView.setItems(itemsObservableList);
    }
}
