package com.example.examen;

import com.example.examen.controller.Controller;
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
    private static List<Long> clientIds = new ArrayList<>();

    private Service instantiateService() {
        //        Repository<String, User> userDbRepository = new UserDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));

        LocationDbRepository locationDbRepository = new LocationDbRepository();
        HotelDbRepository hotelDbRepository = new HotelDbRepository();
        SpecialOfferDbRepository specialOfferDbRepository = new SpecialOfferDbRepository();
        ClientDbRepository clientDbRepository = new ClientDbRepository();
        ReservationDbRepository reservationDbRepository = new ReservationDbRepository();

        return new Service(locationDbRepository, hotelDbRepository, specialOfferDbRepository, clientDbRepository, reservationDbRepository);
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


        clientIds.forEach(clientId -> {
            Stage stage_main = new Stage();
            URL location = getClass().getResource("main.fxml");
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(location);
            AnchorPane root = null;
            try {
                root = loader.load();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            Controller ctrl = loader.getController();
            ctrl.setService(service);
            ctrl.setClient(service.getClient(clientId));
            stage_main.setScene(new Scene(root, 600, 400));
            stage_main.setTitle("Main " + clientId);
            stage_main.show();





            Stage stage_client = new Stage();
            URL location_client = getClass().getResource("client-offers.fxml");
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
            ctrl_client.setClient(service.getClient(clientId));
            stage_client.setScene(new Scene(root_client, 600, 400));
            stage_client.setTitle(String.valueOf(clientId));
            stage_client.show();


        });
    }

    public static void main(String[] args) {
        for(int index = 0; index < args.length; index++) {
            String clientId = args[index].substring(7, args[index].length()-1);
            clientIds.add(Long.valueOf(clientId));
        }
        //System.out.println(clientIds);

        launch();
    }
}