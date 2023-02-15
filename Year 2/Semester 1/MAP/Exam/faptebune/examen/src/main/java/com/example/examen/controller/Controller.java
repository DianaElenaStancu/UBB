package com.example.examen.controller;


import com.example.examen.domain.Persoana;
import com.example.examen.service.Service;

public interface Controller {
    void setService(Service service);

    void setPersoana(Persoana persoana);

}
