package com.example.examen.controller;

import com.example.examen.domain.HotelDTO;
import com.example.examen.service.Service;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;

public abstract class AbstractController implements Controller {

    /**
     * Loads a stage
     * @param service every stage has a Service object for rendering data
     * @param location every stage has a relative path to the .fxml file
     * @param title defines the title of the page
     * @param width defines the width of the page
     * @param height defines the height of the page
     * @throws IOException if an error occurs during loading the root
     */
    public void loadPage(Service service, HotelDTO hotelDTO, URL location, String title, Integer width, Integer height) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(location);
        AnchorPane root = loader.load();
        Controller ctrl = loader.getController();

        if(hotelDTO != null) {
            ctrl.setHotelDTO(hotelDTO);
        }

        if(service != null) {
            ctrl.setService(service);
        }


        Stage stage = new Stage();
        stage.setScene(new Scene(root,  width,  height));
        stage.setTitle(title);
        stage.show();
    }

    /**
     * closes a stage
     * @param stage of type Stage
     */
    public void closePage(Stage stage) {
        stage.close();
    }

    /**
     * sets and shows an information alert
     * @param title defines the title of the alert
     * @param headerText defines the header text of the alert
     * @param contentText defines the conent text of the alert
     */
    public void showInformationAlert(String title, String headerText, String contentText) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(headerText);
        alert.setContentText(contentText);
        alert.show();
    }
}
