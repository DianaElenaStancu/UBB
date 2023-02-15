package com.example.examen.controller;

import com.example.examen.domain.Client;
import com.example.examen.domain.HotelDTO;
import com.example.examen.domain.Location;
import com.example.examen.domain.Reservation;
import com.example.examen.service.Service;
import com.example.examen.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;

import java.io.IOException;
import java.net.URL;
import java.util.Objects;

public class MainController extends AbstractController implements Observer<Reservation> {

    ObservableList<HotelDTO> hotelsModel = FXCollections.observableArrayList();
    ObservableList<Location> locationsModel = FXCollections.observableArrayList();


    public ComboBox locationCombo;
    public TableView tableViewId;
    public TableColumn<HotelDTO, String> locationCol;
    public TableColumn<HotelDTO, String> nameCol;
    public TableColumn<HotelDTO, Integer> noRoomsCol;
    public TableColumn<HotelDTO, Double> priceCol;
    public TableColumn<HotelDTO, String> typeCol;
    private Service service;
    private Client client;
    @Override
    public void setService(Service service) {
        this.service = service;

        this.service.addObservers((Observer) this);
        System.out.println("HERE\n");

        getLocations();
        getHotels(null);
    }

    @Override
    public void setHotel(HotelDTO hotel) {
    }

    @Override
    public void setClient(Client client) {
        this.client = client;
    }

    private void getHotels(Location location) {
        hotelsModel.clear();
        String locationName = "";
        if(location != null)
            locationName = location.getLocationName();
        this.service.getAllHotelsDTOOfLocation(locationName).forEach(hotelDTO -> {
                hotelsModel.add(hotelDTO);
        });
    }

    private void getLocations() {
        locationsModel.clear();
        this.service.getAllLocations().forEach(location -> {
            locationsModel.add(location);
        });
    }

    @FXML
    public void initialize() {
        locationCol.setCellValueFactory(new PropertyValueFactory<>("locationName"));
        nameCol.setCellValueFactory(new PropertyValueFactory<>("hotelName"));
        noRoomsCol.setCellValueFactory(new PropertyValueFactory<>("noRooms"));
        priceCol.setCellValueFactory(new PropertyValueFactory<>("pricePerNight"));
        typeCol.setCellValueFactory(new PropertyValueFactory<>("type"));

        tableViewId.setItems(hotelsModel);
        locationCombo.setItems(locationsModel);
    }

    public void locationOnAction(ActionEvent actionEvent) {
        if (locationCombo.getValue() != null) {
            getHotels((Location) locationCombo.getValue());
        }
    }

    public void tableClicked(MouseEvent mouseEvent) throws IOException {
        if (tableViewId.getSelectionModel().getSelectedItem() != null) {
            HotelDTO hotelDTO = (HotelDTO) tableViewId.getSelectionModel().getSelectedItem();
            URL location = getClass().getResource("/com/example/examen/offers.fxml");
            loadPage(service, client, hotelDTO, location, "Offers " + hotelDTO.getHotelName() + " for " + client.getName(), 600, 400);
        }
    }

    @Override
    public void update(Reservation event) {
        //System.out.println("aici");
        if (this.client.getHobbies() == this.service.getClient((long) event.getClientId()).getHobbies() && client.getId() != event.getClientId()){
            showInformationAlert("info client " + client.getClientId(), "info", "alt client cu acelasi hobby ca tine a rezervat la hotelul" + this.service.getHotelName(event.getHotelId()));
        }
    }
}
