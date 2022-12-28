package socialnetwork.controllers;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import socialnetwork.domain.User;
import socialnetwork.service.NetworkService;

import java.io.IOException;
import java.net.URL;

public abstract class AbstractController implements Controller {

    /**
     * Loads a stage
     * @param networkService every stage has a NetworkService object for rendering data
     * @param user every stage has an associated user
     * @param location every stage has a relative path to the .fxml file
     * @param title defines the title of the page
     * @param width defines the width of the page
     * @param height defines the height of the page
     * @throws IOException if an error occurs during loading the root
     */
    public void loadPage(NetworkService networkService, User user, User pairedUser, URL location, String title, Integer width, Integer height) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(location);
        AnchorPane root = loader.load();
        Controller ctrl = loader.getController();


        if (user != null) {
            ctrl.setUser(user);
        }

        if (pairedUser != null) {
            ctrl.setPairedUser(pairedUser);
        }

        if(networkService != null) {
            ctrl.setService(networkService);
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
