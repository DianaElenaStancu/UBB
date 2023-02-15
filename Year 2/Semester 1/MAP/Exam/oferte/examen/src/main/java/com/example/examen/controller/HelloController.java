package com.example.examen.controller;

import com.example.examen.domain.HotelDTO;
import com.example.examen.service.Service;
import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class HelloController extends AbstractController{
    Service service;
    @FXML
    private Label welcomeText;

    @Override
    public void setService(Service service) {
        this.service = service;
        //set things, observers/onservables
    }

    @Override
    public void setHotelDTO(HotelDTO hotelDTO) {

    }

    @Override
    public void setClient(Integer client) {

    }

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }
}