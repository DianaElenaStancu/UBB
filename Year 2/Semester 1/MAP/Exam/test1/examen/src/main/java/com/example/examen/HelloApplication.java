package com.example.examen;

import com.example.examen.config.ApplicationContext;
import com.example.examen.controller.Controller;
import com.example.examen.controller.HelloController;
import com.example.examen.domain.*;
import com.example.examen.repository.MenuItemDbRepository;
import com.example.examen.repository.OrderTableDbRepository;
import com.example.examen.repository.Repository;
import com.example.examen.repository.TablesDbRepository;
import com.example.examen.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class HelloApplication extends Application {

    private Service instantiateService() {
        //        Repository<String, User> userDbRepository = new UserDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));
        Repository<Integer, Table> tableRepository = new TablesDbRepository();
        Repository<Integer, MenuItem> menuItemRepository = new MenuItemDbRepository();
        Repository<Integer, Order> orderRepository = new OrderTableDbRepository();

        return new Service(tableRepository, menuItemRepository, orderRepository);
    }

    @Override
    public void start(Stage stage) throws IOException {

//
//        URL location = getClass().getResource("hello-view.fxml");
//        Service service = instantiateService();
//        FXMLLoader loader = new FXMLLoader();
//        loader.setLocation(location);
//        AnchorPane root = loader.load();
//        Controller ctrl = loader.getController();
//        ctrl.setService(service);
//        stage.setScene(new Scene(root, 320, 340));
//        stage.setTitle("Main");
//        stage.show();

        Service service = instantiateService();

        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("staff.fxml"));
        AnchorPane root = loader.load();
        Controller ctrl_staff = loader.getController();
        ctrl_staff.setService(service);

        Scene scene = new Scene(root, 1000, 600);
        stage.setTitle("Staff");
        stage.setScene(scene);
        stage.show();


        //afiseaza toate tabelele

        Iterable<Table> tables = service.findAllTables();
        tables.forEach(table -> {
            Stage table_stage = new Stage();
            Scene scene_table;
            FXMLLoader fxmlLoadertable  = new FXMLLoader(getClass().getResource("table-view.fxml"));
            try {
                scene_table = new Scene(fxmlLoadertable.load(), 600, 400);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            Controller ctrl = fxmlLoadertable.getController();
            ctrl.setService(service);
            ctrl.setTable(table);
            table_stage.setTitle(table.toString());
            table_stage.setScene(scene_table);
            table_stage.show();
        });
    }

    public static void main(String[] args) {
        launch();
    }
}