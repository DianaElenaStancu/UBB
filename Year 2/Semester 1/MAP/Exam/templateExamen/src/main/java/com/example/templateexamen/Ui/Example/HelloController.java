package com.example.templateexamen.Ui.Example;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class HelloController {
    @FXML
    private Label welcomeText;

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }
}
/*
public void setService(Service service) {
    this.service = service;
    menuObservableList = FXCollections.observableArrayList();
    initMenu();
    Observable observable = (Observable) service.getOrderRepository();
    observable.addObserver(this);
}
-----------------------------------------------------------------

Alert alert = new Alert(Alert.AlertType.INFORMATION);
alert.setTitle("Table " + order.getTableId());
alert.setHeaderText(null);
alert.showAndWait();
-----------------------------------------------------------------


 */