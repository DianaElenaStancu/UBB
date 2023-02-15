package com.example.examen;

import com.example.examen.controller.Controller;
import com.example.examen.domain.Client;
import com.example.examen.domain.Hotel;
import com.example.examen.domain.Location;
import com.example.examen.domain.SpecialOffer;
import com.example.examen.repository.*;
import com.example.examen.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class HelloApplication extends Application {

    static List<Integer> clients = new ArrayList<>();

    private Service instantiateService() {
        //        Repository<String, User> userDbRepository = new UserDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));
        Repository<Double, Location> locationRepository = new LocationDbRepository();
        Repository<Double, Hotel> hotelRepository = new HotelDbRepository();
        Repository<Double, SpecialOffer> specialOfferRepository = new SpecialOfferDbRepository();
        Repository<Long, Client> clientRepository = new ClientDbRepository();


        return new Service(locationRepository, hotelRepository, specialOfferRepository, clientRepository);
    }

    @Override
    public void start(Stage stage) throws IOException {

        URL location = getClass().getResource("home.fxml");
        Service service = instantiateService();
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(location);
        AnchorPane root = loader.load();
        Controller ctrl = loader.getController();
        ctrl.setService(service);
        stage.setScene(new Scene(root, 600, 400));
        stage.setTitle("Main");
        stage.show();

//        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("hello-view.fxml"));
//        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
//        stage.setTitle("Hello!");
//        stage.setScene(scene);
//        stage.show();


        clients.forEach( client -> {
            Stage stage_client = new Stage();
            URL location_client = getClass().getResource("offer.fxml");
            FXMLLoader loader_client = new FXMLLoader();
            loader_client.setLocation(location_client);
            AnchorPane root_client = null;
            try {
                root_client = loader_client.load();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            Controller ctrl_client = loader_client.getController();
            ctrl_client.setService(service);
            ctrl_client.setClient(client);
            stage_client.setScene(new Scene(root_client, 600, 400));
            stage_client.setTitle(client.toString());
            stage_client.show();
           }
        );
    }

    public static void main(String[] args) {
        for (int i = 0; i < args.length; i++) {
            String id = args[i].substring(7, args[i].length() - 1);
            clients.add(Integer.valueOf(id));
        }

        launch();
    }
}