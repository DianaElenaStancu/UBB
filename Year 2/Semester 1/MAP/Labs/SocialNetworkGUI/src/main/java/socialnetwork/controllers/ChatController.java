package socialnetwork.controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import socialnetwork.domain.User;
import socialnetwork.domain.UserDTO;
import socialnetwork.service.NetworkService;


public class ChatController extends AbstractController{
    NetworkService networkService;

    ObservableList<UserDTO> messagesModel = FXCollections.observableArrayList();


    @FXML
    Button sendMessageButton;
    @FXML
    public void initialize() {

    }

    public void setService(NetworkService networkService){this.networkService = networkService;}
    public void setUser(User user){}
}
