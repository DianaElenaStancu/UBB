package com.example.examen.controller;

import com.example.examen.domain.Client;
import com.example.examen.domain.HotelDTO;
import com.example.examen.domain.SpecialOffer;
import com.example.examen.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListView;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.chrono.ChronoLocalDateTime;

public class OfferController extends AbstractController{

    ObservableList<SpecialOffer> specialOffers = FXCollections.observableArrayList();

    LocalDate startDate = LocalDate.MIN, endDate = LocalDate.MAX;
    public DatePicker startDateId;
    public DatePicker endDateId;
    public ListView offersListViewId;
    private Service service;
    private HotelDTO hotelDTO;

    private Client client;
    @Override
    public void setService(Service service) {
        this.service = service;
    }



    private void getSpecialOffers() {
        specialOffers.clear();
        Double id = Double.valueOf(0);
        if (hotelDTO != null)
            id = hotelDTO.getId();
        System.out.println(client);
        service.getOffersOfHotel(id).forEach(specialOffer -> {
            if (specialOffer.getStartDate().toLocalDate().isAfter(startDate) &&
                    specialOffer.getEndDate().toLocalDate().isBefore(endDate) && (client == null || client.getFidelityGrade() > specialOffer.getPercents()))
                specialOffers.add(specialOffer);
        });
    }



    @Override
    public void setHotelDTO(HotelDTO hotelDTO) {
        this.hotelDTO = hotelDTO;
    }

    @Override
    public void setClient(Integer client) {
        this.client = this.service.findClient(Long.valueOf(client));
        getSpecialOffers();

    }

    @FXML
    public void initialize() {
        offersListViewId.setItems(specialOffers);
    }



    public void startDateOnAction(ActionEvent actionEvent) {
            try {
                if (startDateId.getValue() != null) {
                    startDate = startDateId.getValue();
                    getSpecialOffers();
                }
            } catch (Exception exception) {
                showInformationAlert("", "", exception.toString());
            }

    }

    public void endDateOnAction(ActionEvent actionEvent) {

            try {
                if (endDateId.getValue() != null) {
                    endDate = endDateId.getValue();
                    getSpecialOffers();
                }
            } catch (Exception exception) {
                showInformationAlert("", "", exception.toString());
            }
        }
}
