package socialnetwork.controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import socialnetwork.domain.Message;
import socialnetwork.domain.User;
import socialnetwork.service.NetworkService;

import java.util.List;
import java.util.stream.StreamSupport;


public class ChatController extends AbstractController{
    NetworkService networkService;
    User currentUser, pairedUser;

    @FXML
    Button sendMessageButton;

    @FXML
    TextField messageTextField;

    @FXML
    ListView messagesListView;

    ObservableList<Message> messagesModel = FXCollections.observableArrayList();

    public void setPairedUser(User user) {
        this.pairedUser = user;
    }

    public void setUser(User user) {
        this.currentUser = user;
    }

    public void setService(NetworkService networkService){
        this.networkService = networkService;

        messagesModel.setAll(getMessages());
    }

    private List<Message> getMessages() {
        Iterable<Message> messages = this.networkService.findAllMessages(currentUser.getId(), pairedUser.getId());
        return StreamSupport.stream(messages.spliterator(), false).toList();
    }

    @FXML
    public void initialize() {
        messagesListView.setItems(messagesModel);
    }

    @FXML
    protected void sendMessageButtonClicked(){
        String text = messageTextField.getText();
        if(text.length() != 0) {
            this.networkService.saveMessage(text, currentUser.getId(), pairedUser.getId());
            messagesModel.setAll(getMessages());
            messageTextField.clear();
        }
    }
}
