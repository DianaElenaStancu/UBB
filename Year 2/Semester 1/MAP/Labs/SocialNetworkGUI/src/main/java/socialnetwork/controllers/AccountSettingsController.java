package socialnetwork.controllers;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import socialnetwork.domain.User;
import socialnetwork.service.NetworkService;

import java.io.IOException;
import java.net.URL;
import java.util.Objects;

import static socialnetwork.constants.Strings.*;

public class AccountSettingsController extends AbstractController{

    User currentUser;
    NetworkService networkService;

    @FXML
    Button resetButton, deleteButton;

    @FXML
    TextField firstNameTextField, lastNameTextField, emailTextField, passwordFirstTextField, passwordSecondTextField;

    @FXML
    public void initialize() {
        resetButton.setDefaultButton(true);
    }

    public void setService(NetworkService networkService){
        this.networkService = networkService;
    }

    public void setPairedUser(User user){}

    public void setUser(User user){
        this.currentUser = user;
        firstNameTextField.setPromptText(currentUser.getFirstName());
        lastNameTextField.setPromptText(currentUser.getLastName());
        emailTextField.setPromptText(currentUser.getEmail());
    }

    @FXML
    protected void resetButtonClicked(){
        String firstName, lastName, email, password, passwordAgain;

        firstName = firstNameTextField.getText().isEmpty() ? currentUser.getFirstName() : firstNameTextField.getText();
        lastName = lastNameTextField.getText().isEmpty() ? currentUser.getLastName() : lastNameTextField.getText();
        email = emailTextField.getText().isEmpty() ? currentUser.getEmail() : emailTextField.getText();
        password = passwordFirstTextField.getText().isEmpty() ? currentUser.getPassword() : passwordFirstTextField.getText();
        passwordAgain = passwordSecondTextField.getText();

        if (!passwordAgain.isEmpty() && !Objects.equals(password, passwordAgain)) {
            showInformationAlert(RESET_INFO, OPERATION_FAILED, ADD_THE_SAME_PASSWORD);
        }
        try {
            this.networkService.updateUser(currentUser.getId(), firstName, lastName, email, password);
            currentUser = this.networkService.findUser(currentUser.getId());
            showInformationAlert(RESET_INFO, OPERATION_FINISHED_SUCCESSFULLY, EMPTY);
        } catch(Exception exception) {
            showInformationAlert(RESET_INFO, OPERATION_FINISHED_SUCCESSFULLY, exception.getMessage());
        }

    }

    @FXML
    protected void deleteButtonClicked() throws IOException {

        this.networkService.removeUser(currentUser.getId());

        URL location = getClass().getResource("/socialnetwork/log-in.fxml");
        String title = "Login";
        loadPage(this.networkService, null, null, location, title, 320, 340);

        closePage((Stage) deleteButton.getScene().getWindow());
    }

    @FXML
    protected void backHyperlinkClicked() throws IOException{

        URL location = getClass().getResource("/socialnetwork/home.fxml");
        String title = "Welcome, " + currentUser.getId();
        loadPage(this.networkService, this.currentUser, null, location, title, 1000, 500);

        closePage((Stage) resetButton.getScene().getWindow());
    }
}
