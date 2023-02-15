module com.example.restaurante {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires com.almasb.fxgl.all;
    requires java.sql;

    opens com.example.restaurante to javafx.fxml;
    exports com.example.restaurante;

    opens com.example.restaurante.domain to javafx.fxml;
    exports com.example.restaurante.domain;

    opens com.example.restaurante.controller to javafx.fxml;
    exports com.example.restaurante.controller;
}