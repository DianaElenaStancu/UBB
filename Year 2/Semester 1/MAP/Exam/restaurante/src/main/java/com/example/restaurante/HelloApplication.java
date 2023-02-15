package com.example.restaurante;

import com.example.restaurante.controller.StaffController;
import com.example.restaurante.controller.TableController;
import com.example.restaurante.domain.MenuItem;
import com.example.restaurante.domain.Order;
import com.example.restaurante.domain.Table;
import com.example.restaurante.repository.Repository;
import com.example.restaurante.repository.factory.RepositoryFactory;
import com.example.restaurante.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

import static com.example.restaurante.repository.factory.RepositoryEntity.*;
import static org.controlsfx.glyphfont.FontAwesome.Glyph.USERS;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Repository<Integer, Table> tablesRepository = RepositoryFactory.getInstance().createRepository(TABLES);
        Repository<Integer, Order> ordersRepository = RepositoryFactory.getInstance().createRepository(ORDERS);
        Repository<Integer, MenuItem> menuItemsRepository = RepositoryFactory.getInstance().createRepository(MENUITEMS);
        Service service = new Service(tablesRepository, ordersRepository, menuItemsRepository);

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("staff-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 640, 480);

        StaffController staffController = fxmlLoader.getController();
        staffController.setService(service);

        stage.setTitle("Staff");
        stage.setScene(scene);
        stage.show();

        service.getAllTables().forEach(table -> {
            FXMLLoader table_loader = new FXMLLoader(HelloApplication.class.getResource("table-view.fxml"));
            Stage table_stage = new Stage();
            Scene table_scene;
            try {
                table_scene = new Scene(table_loader.load(), 320, 240);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            TableController tableController = table_loader.getController();
            tableController.setTable(table);
            tableController.setService(service);

            table_stage.setTitle("Table " + table.getId());
            table_stage.setScene(table_scene);
            table_stage.show();
        });
    }

    public static void main(String[] args) {
        launch();
    }
}