package com.example.examen.controller;

import com.example.examen.domain.HotelDTO;
import com.example.examen.service.Service;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;

public class ClientOfferController extends AbstractController{
    public TableColumn hotelCol;
    public TableColumn locatieCol;
    public TableColumn startCol;
    public TableColumn endCol;
    public TableView ofertaTableView;

    @Override
    public void setService(Service service) {

    }

    @Override
    public void setHotelDTO(HotelDTO hotelDTO) {

    }

    @Override
    public void setClient(Integer client) {

    }
}
