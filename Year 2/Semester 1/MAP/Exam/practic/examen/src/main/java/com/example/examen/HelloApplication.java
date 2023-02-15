package com.example.examen;

import com.example.examen.controller.Controller;
import com.example.examen.repository.CityDbRepository;
import com.example.examen.repository.TrainStationsDbRepository;
import com.example.examen.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;

public class HelloApplication extends Application {

    private Service instantiateService() {
        CityDbRepository cityDbRepository = new CityDbRepository();
        TrainStationsDbRepository trainStationsDbRepository = new TrainStationsDbRepository();

        return new Service(cityDbRepository, trainStationsDbRepository);
    }

    @Override
    public void start(Stage stage) throws IOException {

        URL location = getClass().getResource("start.fxml");
        Service service = instantiateService();
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(location);
        AnchorPane root = loader.load();
        Controller ctrl = loader.getController();
        ctrl.setService(service);
        ctrl.setClientId(0);
        stage.setScene(new Scene(root, 600, 400));
        stage.setTitle("Start");
        stage.show();

//        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("hello-view.fxml"));
//        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
//        stage.setTitle("Hello!");
//        stage.setScene(scene);
//        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}