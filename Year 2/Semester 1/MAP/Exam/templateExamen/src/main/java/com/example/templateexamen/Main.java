package com.example.templateexamen;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("Example/hello_view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 500, 300);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
/*
public void start(Stage stage) throws IOException {
    Repository<Integer, Table> tableRepository = new TableDbRepository();
    Repository<Integer, MenuItem> menuRepository = new MenuDbRepository();
    Repository<Integer, Order> orderRepository = new OrderDbRepository();
    Service service = new Service(tableRepository, menuRepository, orderRepository);

    FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("staff_view.fxml"));
    Scene scene = null;
    try {
        scene = new Scene(fxmlLoader.load(), 320, 240);
    } catch (IOException e) {
        throw new RuntimeException(e);
    }
    StaffController controller = (StaffController)fxmlLoader.getController();
    controller.setService(service);

    stage.setTitle("Staff");
    stage.setScene(scene);
    stage.show();

    service.getTableRepository().findAll().forEach(table -> {
        FXMLLoader fxmlLoaderTable = new FXMLLoader(HelloApplication.class.getResource("table_view.fxml"));
        Stage stageTable = new Stage();
        Scene sceneTable = null;
        try {
            sceneTable = new Scene(fxmlLoaderTable.load(), 320, 240);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        TableController tableController = (TableController)fxmlLoaderTable.getController();
        tableController.setTable(table);
        tableController.setService(service);

        stageTable.setTitle("Table" + table.getId());
        stageTable.setScene(sceneTable);
        stageTable.show();
    });
}
 */