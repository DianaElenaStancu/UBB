package com.example.examen.controller;

import com.example.examen.domain.Table;
import com.example.examen.service.Service;
import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class HelloController extends AbstractController{
    Service service;
    @FXML
    private Label welcomeText;

    public void setTable(Table table){}
    @Override
    public void setService(Service service) {
        this.service = service;
        //set things, observers/onservables
    }

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }
}