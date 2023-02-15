package com.example.examen.controller;


import com.example.examen.domain.HotelDTO;
import com.example.examen.service.Service;

public interface Controller {
    void setService(Service service);

    void setHotelDTO(HotelDTO hotelDTO);

    void setClient(Integer client);
}
