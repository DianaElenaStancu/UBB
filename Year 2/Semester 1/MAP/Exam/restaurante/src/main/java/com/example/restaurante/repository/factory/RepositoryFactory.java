package com.example.restaurante.repository.factory;

import com.example.restaurante.ApplicationContext;
import com.example.restaurante.Config;
import com.example.restaurante.domain.MenuItem;
import com.example.restaurante.domain.Order;
import com.example.restaurante.domain.Table;
import com.example.restaurante.repository.Repository;
import com.example.restaurante.repository.database.MenuItemsDbRepository;
import com.example.restaurante.repository.database.OrdersDbRepository;
import com.example.restaurante.repository.database.TablesDbRepository;
import javafx.scene.control.Menu;
import javafx.util.Pair;

public class RepositoryFactory {

    private static RepositoryFactory instance = new RepositoryFactory();

    private static Repository<Integer, Table> createTablesRepository() {
        return new TablesDbRepository("jdbc:postgresql://localhost:5432/restaurants",
                    "postgres", "parola");
    }

    private static Repository<Integer, Order> createOrdersRepository() {
            return new OrdersDbRepository("jdbc:postgresql://localhost:5432/restaurants",
                    "postgres", "parola");
    }

    private static Repository<Integer, MenuItem> createMenuItemsRepository() {
        return new MenuItemsDbRepository("jdbc:postgresql://localhost:5432/restaurants",
                "postgres", "parola");
    }

    public Repository createRepository(RepositoryEntity repositoryEntity) {
        switch (repositoryEntity) {
            case TABLES:
                return createTablesRepository();
            case ORDERS:
                return createOrdersRepository();
            default:
                return createMenuItemsRepository();
        }
    }

    /**
     * Method that retuns the instance of the repository factory
     * @return the repository factory
     */
    public static RepositoryFactory getInstance() {
        return instance;
    }
}
