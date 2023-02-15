package com.example.examen.controller;

import com.example.examen.domain.HotelDTO;
import com.example.examen.domain.Location;
import com.example.examen.domain.Type;
import com.example.examen.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.io.IOException;
import java.net.URL;
import java.util.List;
import java.util.Objects;
import java.util.function.Predicate;

public class HomeController extends AbstractController{
    private Service service;
    ObservableList<HotelDTO> hotelsModel = FXCollections.observableArrayList();
    ObservableList<Location> locationsModel = FXCollections.observableArrayList();



    @FXML
    TableView hotelTableViewId;

    @FXML
    TableColumn<HotelDTO, String> locationColId, nameColId;

    @FXML
    TableColumn<HotelDTO, Integer> noRoomsColId;

    @FXML
    TableColumn<HotelDTO, Double> pricePerNightColId;

    @FXML
    TableColumn<HotelDTO, Type> typeColId;

    @FXML
    ComboBox locationComboId;

    @Override
    public void setService(Service service) {
        this.service = service;

        this.service.getAllLocations().forEach(location -> {locationsModel.add(location);});
        getHotels(null);
    }

    @Override
    public void setHotelDTO(HotelDTO hotelDTO) {

    }

    @Override
    public void setClient(Integer client) {
    }

    @FXML
    public void initialize() {
        locationColId.setCellValueFactory(new PropertyValueFactory<>("locationName"));
        nameColId.setCellValueFactory(new PropertyValueFactory<>("hotelName"));
        noRoomsColId.setCellValueFactory(new PropertyValueFactory<>("noRooms"));
        pricePerNightColId.setCellValueFactory(new PropertyValueFactory<>("pricePerNight"));
        typeColId.setCellValueFactory(new PropertyValueFactory<>("type"));

        //locationComboId
        locationComboId.setItems(locationsModel);
        hotelTableViewId.setItems(hotelsModel);

        //hotelTableViewId.getSelectionModel().
    }

    @FXML
    public void locationComboOnAction() {
        Location location = (Location) locationComboId.getValue();
        if (location != null) {
            getHotels(location);
        }
    }

    private void getHotels(Location location) {
        hotelsModel.clear();
        service.getAllHotelsDTO().forEach(hotelDTO -> {
            if (location == null || Objects.equals(hotelDTO.getLocationName(), location.getLocationaName()))
                hotelsModel.add(hotelDTO);
        });
    }

    @FXML
    public void hotelTableViewOnMousePressed() throws IOException {
        HotelDTO hotelDTO = (HotelDTO) hotelTableViewId.getSelectionModel().getSelectedItem();
       // System.out.println(hotelTableViewId.getSelectionModel().getSelectedItem());
        if(hotelDTO != null) {
            //load page

            URL location =getClass().getResource("/com/example/examen/offer.fxml");
            loadPage(service, hotelDTO, location, "oferte", 600, 400);
        }
    }
}
