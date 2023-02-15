module com.example.templateexamen {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.example.templateexamen to javafx.fxml;
    exports com.example.templateexamen;
    //exports com.example.templateexamen.Ui;
    //opens com.example.templateexamen.Ui to javafx.fxml;
    exports com.example.templateexamen.Ui.Example;
    opens com.example.templateexamen.Ui.Example to javafx.fxml;
    exports com.example.templateexamen.Repository.Example;
    exports com.example.templateexamen.Domain;
    exports com.example.templateexamen.Domain.Example;
}