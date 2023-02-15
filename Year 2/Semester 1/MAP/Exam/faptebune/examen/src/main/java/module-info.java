module com.example.examen {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.example.examen to javafx.fxml;
    exports com.example.examen;
    exports com.example.examen.controller;
    exports com.example.examen.domain;
    opens com.example.examen.controller to javafx.fxml;
}