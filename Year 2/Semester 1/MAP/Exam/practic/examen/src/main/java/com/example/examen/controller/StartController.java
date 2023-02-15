package com.example.examen.controller;

import com.example.examen.service.Service;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;

import java.net.URL;

public class StartController extends AbstractController{
    public Button openButtonId;
    private int clientId;

    private Service service;

    public void openButtonClicked(ActionEvent actionEvent) {
        try{
            clientId++;
            URL location = getClass().getResource("/com/example/examen/main.fxml");
            loadPage(service, clientId, location, "Main", 600, 400);
        } catch(Exception exception){
            showInformationAlert("", "", exception.getMessage());
        }
    }

    @Override
    public void setService(Service service) {
        this.service = service;
    }

    @Override
    public void setClientId(int id) {
        this.clientId = id;
    }
}
