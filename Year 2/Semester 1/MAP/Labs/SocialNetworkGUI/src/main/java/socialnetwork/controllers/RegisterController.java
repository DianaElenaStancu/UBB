package socialnetwork.controllers;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import socialnetwork.domain.User;
import socialnetwork.service.NetworkService;

import java.io.IOException;
import java.net.URL;

import static socialnetwork.constants.Strings.*;

public class RegisterController extends AbstractController{

    private NetworkService networkService;
    @FXML
    Button signUpButton;

    @FXML
    TextField usernameTextField, firstNameTextField, lastNameTextField, emailTextField, passwordTextField;


    @FXML
    public void initialize() {
        signUpButton.setDefaultButton(true);
    }
    public void setService(NetworkService networkService) {
        this.networkService = networkService;
    }

    public void setUser(User user) {}

    public void setPairedUser(User user){}

    @FXML
    protected void loginHyperlinkClicked() throws IOException {
        URL location = getClass().getResource("/socialnetwork/log-in.fxml");
        loadPage(this.networkService, null, null, location, LOG_IN, 320, 340);

        closePage((Stage) signUpButton.getScene().getWindow());
    }

    @FXML
    protected void signUpButtonClicked() {
        String username, firstName, lastName, email, password;
        username = usernameTextField.getText();
        firstName = firstNameTextField.getText();
        lastName = lastNameTextField.getText();
        email = emailTextField.getText();
        password = passwordTextField.getText();

        try {
            this.networkService.addUser(username, firstName, lastName, email, password);

            URL location = getClass().getResource("/socialnetwork/home.fxml");
            String title = "Welcome, " + username;
            User user = new User(username, firstName, lastName, email, password);
            loadPage(this.networkService, user, null, location, title, 1000, 500);

            closePage((Stage) signUpButton.getScene().getWindow());
        } catch (Exception exception) {
            showInformationAlert(SIGN_UP_INFO, OPERATION_FAILED, exception.getMessage());
        }

    }
}