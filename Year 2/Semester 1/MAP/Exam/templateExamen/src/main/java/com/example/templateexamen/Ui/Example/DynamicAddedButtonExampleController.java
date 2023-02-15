package com.example.templateexamen.Ui.Example;

import com.example.templateexamen.Domain.Example.ExampleEntity;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.Callback;

import java.util.ArrayList;
import java.util.List;

public class DynamicAddedButtonExampleController {
    @FXML
    TableView<ExampleEntity> exampleTableView;
    ObservableList<ExampleEntity> exampleEntities;
    @FXML
    TableColumn<ExampleEntity, String> exampleTableColumnName;
    @FXML
    TableColumn<ExampleEntity, String> exampleTableColumnButton;

    /**
     * called after the view were created
     */
    @FXML
    private void initialize() {
        initTableView();
        updateTableView();
    }

    private void updateTableView() {
        List<ExampleEntity> entities = new ArrayList<>();
        for(int i=0; i<10; i++)
            entities.add(new ExampleEntity(i, "name" + i));
        this.exampleEntities = FXCollections.observableArrayList(entities);
        this.exampleTableView.setItems(this.exampleEntities);
    }

    private void initTableView() {
        exampleTableColumnName.setCellValueFactory(new PropertyValueFactory<ExampleEntity, String>("name"));
        Callback<TableColumn<ExampleEntity, String>, TableCell<ExampleEntity, String>> cellFactory = new Callback<>() {
            public TableCell call(TableColumn<ExampleEntity, String> param) {
                TableCell<ExampleEntity, String> cell = new TableCell<>() {
                    final Button btn = new Button("Do something");

                    public void updateItem(String item, boolean empty) {
                        super.updateItem(item, empty);
                        if (empty) {
                            this.setGraphic((Node) null);
                            this.setText((String) null);
                        } else {
                            this.btn.setOnAction((event) -> {
                                ExampleEntity order = (ExampleEntity) this.getTableView().getItems().get(this.getIndex());
                                System.out.println(order.getName());
                            });
                            this.setGraphic(this.btn);
                            this.setText((String) null);
                        }
                    }
                };
                return cell;
            }
        };
        this.exampleTableColumnButton.setCellFactory(cellFactory);
    }
}


/*
public void start(Stage stage) throws IOException {
    FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("dynamic_added_button_example_view.fxml"));
    Scene scene = new Scene(fxmlLoader.load(), 500, 300);
    stage.setTitle("Hello!");
    stage.setScene(scene);
    stage.show();
}
 */