package com.example.examen.controller;


import com.example.examen.domain.Client;
import com.example.examen.domain.HotelDTO;
import com.example.examen.service.Service;

public interface Controller {
    void setService(Service service);

    void setHotel(HotelDTO hotel);

    void setClient(Client client);

}
