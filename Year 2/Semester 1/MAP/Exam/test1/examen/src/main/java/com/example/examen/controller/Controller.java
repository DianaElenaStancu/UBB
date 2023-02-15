package com.example.examen.controller;


import com.example.examen.domain.Table;
import com.example.examen.service.Service;

import java.net.URL;

public interface Controller {
    void setService(Service service);

    void setTable(Table table);
}
