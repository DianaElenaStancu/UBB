module socialnetwork.socialnetworkgui {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens socialnetwork to javafx.fxml;
    exports socialnetwork;
    exports socialnetwork.controllers;
    exports socialnetwork.service;
    exports socialnetwork.domain;
    exports socialnetwork.repository;
    exports socialnetwork.domain.validators;
    exports socialnetwork.domain.exceptions;
    opens socialnetwork.controllers to javafx.fxml;
}