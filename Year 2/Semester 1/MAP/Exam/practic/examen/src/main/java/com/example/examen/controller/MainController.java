package com.example.examen.controller;

import com.example.examen.domain.City;
import com.example.examen.domain.Event;
import com.example.examen.service.Service;
import com.example.examen.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.*;

import java.util.List;
import java.util.Objects;

public class MainController extends AbstractController implements Observer<Event> {

    private int clientId;
    public ComboBox departureCityId;
    public ComboBox destinationCityId;
    public CheckBox routeCheckId;
    public Button searchButtonId;
    public ListView routesListId;
    public Label notificationId;

    private Service service;
    private City destinationCity, departureCity;

    ObservableList<City> cityModels= FXCollections.observableArrayList();
    ObservableList<String>  routesModels= FXCollections.observableArrayList();


    @Override
    public void setService(Service service) {
        this.service = service;
        this.service.addObserver(this);
        getCities();
    }

    @Override
    public void setClientId(int id) {
        this.clientId = id;
    }

    private void getCities() {
        cityModels.clear();
        cityModels.addAll(this.service.getAllCities());
    }

    public void initialize() {
        departureCityId.setItems(cityModels);
        destinationCityId.setItems(cityModels);
        routesListId.setItems(routesModels);
    }

    public void departureCityOnAction(ActionEvent actionEvent) {
        notificationId.setText("");
       // service.removePers(departureCity, destinationCity, clientId);
        departureCity = (City) departureCityId.getValue();
    }

    public void destinationCityOnAction(ActionEvent actionEvent) {
        notificationId.setText("");
       // service.removePers(departureCity, destinationCity, clientId);
        destinationCity = (City) destinationCityId.getValue();
    }

    public void routeCheckOnAction(ActionEvent actionEvent) {

    }

    public void searchButtonOnAction(ActionEvent actionEvent) {
        try{
            if(destinationCityId.getValue() != null && departureCityId.getValue() != null) {
                if(routeCheckId.isSelected()) {
                    getRoutes(true);
                } else {
                    getRoutes(false);
                }
            }
        } catch(Exception exception) {
            showInformationAlert("", "", exception.getMessage());
        }
    }

    private void getRoutes(boolean direct) {
        routesModels.clear();
        List<String> routesList = service.getRoutes(this.departureCity, this.destinationCity, direct, clientId);
        routesModels.addAll(service.getListWithPrices(routesList));
    }


    public void routesListOnAction(ListView.EditEvent editEvent) {
    }

    @Override
    public void update(Event event) {
        if (Objects.equals(event.getCities().get(0), departureCity.getId()) &&
                Objects.equals(event.getCities().get(1), destinationCity.getId()) && event.getCount() > 1) {
            //showInformationAlert("info", "info", (event.getCount()-1)+" pers se uita la ruta aceasta");
            String notification = "inca "+(event.getCount()-1)+" pers se uita la ruta aceasta";
            notificationId.setText(notification);
        }
    }
}
