package com.example.examen.controller;

import com.example.examen.domain.Nevoie;
import com.example.examen.domain.NevoieDTO;
import com.example.examen.domain.Persoana;
import com.example.examen.service.Service;
import com.example.examen.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;

import java.util.Objects;

public class MainController extends AbstractController implements Observer<Nevoie> {

    public TableView nevoiUserId;
    public TableColumn nevoieCol1;
    public TableColumn salvatorCol1;
    public TextField titluId;
    public TextField descriereId;
    public DatePicker deadlineId;
    public Button adaugaButtonId;
    ObservableList<NevoieDTO>  nevoiModels= FXCollections.observableArrayList();
    ObservableList<NevoieDTO>  nevoiUserModels= FXCollections.observableArrayList();

    public TableView nevoiId;
    public TableColumn nevoieCol;
    public TableColumn salvatorCol;
    private Service service;
    private Persoana persoana;
    @Override
    public void setService(Service service) {
        this.service = service;
        this.service.addObserver(this);
    }

    public void setPersoana(Persoana persoana) {

        this.persoana = persoana;

        getNevoi(persoana);
        getNevoiUser(persoana);
    }

    private void getNevoi(Persoana persoana) {
        nevoiModels.clear();
        nevoiModels.addAll(this.service.getNevoieDTOinTown(persoana));
    }

    private void getNevoiUser(Persoana persoana) {
        nevoiUserModels.clear();
        nevoiUserModels.addAll(this.service.getNevoieDTOOfPerson(persoana));
    }

    public void initialize() {
        nevoieCol.setCellValueFactory(new PropertyValueFactory<>("omInNevoieNume"));
        salvatorCol.setCellValueFactory(new PropertyValueFactory<>("omSalvator"));

        nevoieCol1.setCellValueFactory(new PropertyValueFactory<>("omInNevoieNume"));
        salvatorCol1.setCellValueFactory(new PropertyValueFactory<>("omSalvator"));

        nevoiId.setItems(nevoiModels);
        nevoiUserId.setItems(nevoiUserModels);
    }

    public void nevoiOnAction() {
        if (nevoiId.getSelectionModel().getSelectedItem() != null) {
            try {
                NevoieDTO nevoieDTO = (NevoieDTO) nevoiId.getSelectionModel().getSelectedItem();
                if (Objects.equals(nevoieDTO.getOmSalvator(), "")) {
                    Nevoie nevoie = this.service.findNevoie(nevoieDTO.getId());
                    nevoie.setOmSalvator(persoana.getId());
                    nevoie.setStatus("Erou gasit!");
                    this.service.updateNevoie(nevoie);
                    showInformationAlert("info", "succes", "nevoie atribuita cu succes");
                    getNevoi(persoana);
                    getNevoiUser(persoana);
                } else {
                    showInformationAlert("info", "fail", "nevoia e deja atribuita");

                }
            } catch (Exception exception) {
                showInformationAlert("info", "fail", exception.getMessage());
            }
        }
    }

    public void nevoiUserOnAction(MouseEvent mouseEvent) {
    }

    public void adaugaButtonOnAction(ActionEvent actionEvent) {
        try {
            if (!Objects.equals(titluId.getText(), "") && !Objects.equals(descriereId.getText(), "") && !deadlineId.getValue().toString().equals("")) {
                Nevoie nevoie = new Nevoie(titluId.getText(), descriereId.getText(), deadlineId.getValue().atStartOfDay(), persoana.getId(), 0, "Caut erou!");
                this.service.saveNevoie(nevoie);
                showInformationAlert("info", "succes", "nevoie adaugata");
                getNevoi(persoana);
                getNevoiUser(persoana);
            }
        } catch (Exception exception) {
            showInformationAlert("info", "eroare", exception.getMessage());
        }
    }

    @Override
    public void update(Nevoie event) {
        getNevoiUser(persoana);
        getNevoi(persoana);
    }
}
