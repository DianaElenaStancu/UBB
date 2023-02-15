package com.example.examen;

import com.example.examen.controller.Controller;
import com.example.examen.domain.validators.ValidatorPersoana;
import com.example.examen.repository.NevoiDbRepository;
import com.example.examen.repository.PersoaneDbRepository;
import com.example.examen.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;

public class HelloApplication extends Application {

    private Service instantiateService() {
        //        Repository<String, User> userDbRepository = new UserDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
        //                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));
        PersoaneDbRepository persoaneDbRepository = new PersoaneDbRepository();
        ValidatorPersoana validatorPersoana = new ValidatorPersoana();
        persoaneDbRepository.setValidator(validatorPersoana);
        NevoiDbRepository nevoiDbRepository = new NevoiDbRepository();
        return new Service(persoaneDbRepository, nevoiDbRepository);
    }

    @Override
    public void start(Stage stage) throws IOException {
        Service service = instantiateService();


        URL location = getClass().getResource("login.fxml");
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(location);
        AnchorPane root = loader.load();
        Controller ctrl = loader.getController();
        ctrl.setService(service);
        stage.setScene(new Scene(root, 600, 400));
        stage.setTitle("login");
        stage.show();

    }

    public static void main(String[] args) {
        launch();
    }
}