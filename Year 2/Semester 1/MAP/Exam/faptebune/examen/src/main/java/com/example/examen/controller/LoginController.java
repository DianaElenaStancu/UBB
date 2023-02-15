package com.example.examen.controller;

import com.example.examen.domain.Oras;
import com.example.examen.domain.Persoana;
import com.example.examen.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;

import java.io.IOException;
import java.net.URL;

public class LoginController extends AbstractController{

    ObservableList<Persoana> persoanaObservableList = FXCollections.observableArrayList();
    public TextField numeId;
    public TextField prenumeId;
    public TextField usernameId;
    public TextField parolaId;
    public TextField stradaId;
    public TextField numarStradaId;
    public TextField telefonId;
    public ComboBox orasId;
    public ComboBox userId;
    private Service service;

    public void initialize(){
        orasId.getItems().setAll(Oras.values());
        userId.setItems(persoanaObservableList);
    }
    @Override
    public void setService(Service service) {
        this.service = service;

        getPersoane();
    }

    @Override
    public void setPersoana(Persoana persoana) {

    }

    private void getPersoane() {
        persoanaObservableList.setAll(this.service.getPersoane());
    }

    public void userComboOnAction(ActionEvent actionEvent) throws IOException {
        Persoana persoana = (Persoana) userId.getValue();
        URL location =  getClass().getResource("/com/example/examen/main.fxml");
        loadPage(service, persoana, location, "Main " + persoana.getUsername(), 600, 400);
    }

    public void inregistrareOnAction(ActionEvent actionEvent) {
        try {
            String nume = numeId.getText();
            String prenume = prenumeId.getText();
            String username = usernameId.getText();
            String parola = parolaId.getText();
            Oras oras = Oras.valueOf(orasId.getValue().toString());
            String strada = stradaId.getText();
            String numarStrada = numarStradaId.getText();
            String telefon = telefonId.getText();

            Persoana persoana = new Persoana(nume, prenume, username, parola, oras, strada, numarStrada, telefon);
            this.service.savePerson(persoana);

            getPersoane();

            //showInformationAlert("succes", "inregistrare", "succes");
            URL location =  getClass().getResource("/com/example/examen/main.fxml");
            loadPage(service, persoana, location, "Main " + persoana.getUsername(), 600, 400);
        } catch(Exception exception) {
            showInformationAlert("info", "eroare", exception.toString());
        }
    }
}
