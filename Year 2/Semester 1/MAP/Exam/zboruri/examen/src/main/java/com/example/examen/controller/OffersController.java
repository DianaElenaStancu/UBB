package com.example.examen.controller;

import com.example.examen.domain.Client;
import com.example.examen.domain.HotelDTO;
import com.example.examen.domain.Reservation;
import com.example.examen.domain.SpecialOffer;
import com.example.examen.service.Service;
import com.example.examen.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListView;

import java.time.DateTimeException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Period;

public class OffersController extends AbstractController{

    public Button rezervaId;
    ObservableList<SpecialOffer> specialOffers = FXCollections.observableArrayList();

    LocalDate startDate = LocalDate.MIN;
    LocalDate endDate = LocalDate.MAX;
    public ListView listViewId;
    public DatePicker startId;
    public DatePicker endId;
    private Service service;

    private HotelDTO hotelDTO;
    private Client client;

    @Override
    public void setService(Service service) {
        this.service = service;
        //
    }

    private void getSpecialOffers() {
        specialOffers.clear();
        this.service.getSpecialOffersOfHotelInRange(hotelDTO.getHotelId(), startDate, endDate).forEach(
                specialOffer -> {
                        specialOffers.add(specialOffer);
                }
        );
    }

    @FXML
    public void initialize() {
        listViewId.setItems(specialOffers);
    }
    @Override
    public void setHotel(HotelDTO hotel) {
        hotelDTO = hotel;
        getSpecialOffers();
    }

    @Override
    public void setClient(Client client) {
        this.client = client;
    }

    public void startAction(ActionEvent actionEvent) {
        try {
            startDate = startId.getValue();
            getSpecialOffers();

        } catch(Exception exception) {
            showInformationAlert("", "", "Data necorespunzatoare");
        }
    }

    public void endAction(ActionEvent actionEvent) {
        try {
            endDate = endId.getValue();
            getSpecialOffers();

        }
        catch(Exception exception) {
            showInformationAlert("", "", "Data necorespunzatoare");
        }
    }

    public void rezervaClicked(ActionEvent actionEvent) {
        if (listViewId.getSelectionModel().getSelectedItem() != null) {
            SpecialOffer specialOffer = (SpecialOffer) listViewId.getSelectionModel().getSelectedItem();
            Period noNights = Period.between(specialOffer.getStartDate(), specialOffer.getEndDate());
            try{
                this.service.saveReservation(new Reservation(client.getId()+ hotelDTO.getHotelId()+LocalDateTime.now().getNano(),
                        client.getClientId(),
                        hotelDTO.getHotelId(), LocalDateTime.now(), noNights.getDays()));

                showInformationAlert("rezervare", "succes", "rezervare facuta cu succes");
            }catch (Exception exception) {
                showInformationAlert("", "", exception.toString());
            }
        }
    }

}
