package com.example.examen.controller;

import com.example.examen.domain.Client;
import com.example.examen.domain.HotelDTO;
import com.example.examen.domain.SpecialOffer;
import com.example.examen.domain.SpecialOfferDTO;
import com.example.examen.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;

public class ClientOfferController extends AbstractController{
    ObservableList<SpecialOfferDTO> specialOffers = FXCollections.observableArrayList();

    public TableView tableViewId;
    public TableColumn hotelCol;
    public TableColumn locateCol;
    public TableColumn startCol;
    public TableColumn endCol;
    private Service service;

    private Client client;
    @Override
    public void setService(Service service) {
        this.service = service;
    }

    @Override
    public void setHotel(HotelDTO hotel) {

    }

    public void initialize() {
        hotelCol.setCellValueFactory(new PropertyValueFactory<>("hotelName"));
        locateCol.setCellValueFactory(new PropertyValueFactory<>("locationName"));
        startCol.setCellValueFactory(new PropertyValueFactory<>("startDate"));
        endCol.setCellValueFactory(new PropertyValueFactory<>("endDate"));


        tableViewId.setItems(specialOffers);
    }
    @Override
    public void setClient(Client client) {
        this.client = client;

        getSpecialOffers();
    }

    private void getSpecialOffers() {
        this.service.getSpecialOffersOfClient(client).forEach(specialOffer
        -> {
            specialOffers.add(specialOffer);
        });
    }
}
