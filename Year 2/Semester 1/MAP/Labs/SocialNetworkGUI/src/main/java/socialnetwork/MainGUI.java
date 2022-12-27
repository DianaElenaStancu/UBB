package socialnetwork;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import socialnetwork.config.ApplicationContext;
import socialnetwork.controllers.Controller;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.FriendshipValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.FriendshipsDbRepository;
import socialnetwork.repository.database.MessagesDbRepository;
import socialnetwork.repository.database.UserDbRepository;
import socialnetwork.service.NetworkService;

import java.io.IOException;
import java.net.URL;
import java.util.Set;

import static socialnetwork.constants.Strings.LOG_IN;

public class MainGUI extends Application{
    /**
     * creates a NetworkService which contains:
     * UserValidator
     * FriendshipValidator
     * Repository for users
     * Repository for friendships
     * @return networkService
     */
    private NetworkService instantiateService() {
        UserValidator userValidator = new UserValidator();
        FriendshipValidator friendshipValidator = new FriendshipValidator();
        Repository<String, User> userDbRepository = new UserDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));

        Repository<Set<String>, Friendship> friendshipDbRepository = new FriendshipsDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));

        MessagesDbRepository messagesDbRepository = new MessagesDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));
        return new NetworkService(userDbRepository, userValidator, friendshipDbRepository, friendshipValidator, messagesDbRepository);
    }

    @Override
    public void start(Stage stage) throws IOException {
        URL location = getClass().getResource("log-in.fxml");
        NetworkService networkService = instantiateService();
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(location);
        AnchorPane root = loader.load();
        Controller ctrl = loader.getController();
        ctrl.setService(networkService);
        stage.setScene(new Scene(root,  320,  340));
        stage.setTitle(LOG_IN);
        stage.show();
    }
    public static void main(String[] args) {
        launch();
    }
}