package socialnetwork.controllers;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import socialnetwork.domain.User;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.service.NetworkService;
import java.io.IOException;
import java.net.URL;

import static socialnetwork.constants.Strings.*;
import static socialnetwork.gui_utils.GUIUtils.*;


public class LoginController implements Controller{
    private NetworkService networkService;
    @FXML
    Button loginButton;
    @FXML
    TextField usernameTextField;
    @FXML
    TextField passwordTextField;

    @FXML
    public void initialize() {
        loginButton.setDefaultButton(true);
    }

    @Override
    public void setService(NetworkService networkService) {
        this.networkService = networkService;
    }

    @Override
    public void setUser(User user) {}

    @FXML
    protected void loginButtonClicked() throws IOException{
        String username = usernameTextField.getText();
        String password = passwordTextField.getText();

        if (username != null & password != null) {
            try {
                User user = this.networkService.findUser(username);
                if (!this.networkService.verifyCredentials(user, password)) {
                    showInformationAlert(LOG_IN_INFO, OPERATION_FAILED, WRONG_PASSWORD_OR_USERNAME);
                    return;
                }

                URL location = getClass().getResource("/socialnetwork/home.fxml");
                String title = "Welcome, " + user.getFirstName();
                loadPage(this.networkService, user, location, title, 1000, 500);

                closePage((Stage) loginButton.getScene().getWindow());

            } catch (EntityMissingException entityMissingException) {
                showInformationAlert(LOG_IN_FAILED, INVALID_CREDENTIALS, entityMissingException.getMessage());
            }
        }
    }


    @FXML
    protected void registerHyperlinkClicked() throws IOException {
        URL location = getClass().getResource("/socialnetwork/register.fxml");
        loadPage(this.networkService, null, location, REGISTER, 320, 520);

        closePage((Stage) loginButton.getScene().getWindow());
    }
}