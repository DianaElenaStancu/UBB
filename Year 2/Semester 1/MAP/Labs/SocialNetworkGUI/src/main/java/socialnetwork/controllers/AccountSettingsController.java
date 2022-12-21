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

import static socialnetwork.gui_utils.GUIUtils.*;

public class AccountSettingsController implements Controller{

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

    public void setService(NetworkService networkService) {
        this.networkService = networkService;
    }

    public void setUser(User user) {
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
            showInformationAlert("Reset failed", "Incorrect password", "Please add the same password");
        }
        try {
            this.networkService.updateUser(currentUser.getId(), firstName, lastName, email, password);
            currentUser = this.networkService.findUser(currentUser.getId());
            showInformationAlert("Reset successfully", "", "");
        } catch(Exception exception) {
            showInformationAlert("Reset failed", "Something went wrong", exception.getMessage());
        }

    }

    @FXML
    protected void deleteButtonClicked() throws IOException {

        this.networkService.removeUser(currentUser.getId());

        URL location = getClass().getResource("/socialnetwork/log-in.fxml");
        String title = "Login";
        loadPage(this.networkService, null, location, title, 320, 340);

        closePage((Stage) deleteButton.getScene().getWindow());
    }

    @FXML
    protected void backHyperlinkClicked() throws IOException{

        URL location = getClass().getResource("/socialnetwork/home.fxml");
        String title = "Welcome, " + currentUser.getId();
        loadPage(this.networkService, this.currentUser, location, title, 1000, 500);

        closePage((Stage) resetButton.getScene().getWindow());
    }
}
