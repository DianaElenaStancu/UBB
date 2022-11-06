package diana;//import config.ApplicationContext;
//import config.Config;
import diana.config.Config;
import diana.domain.User;
import diana.domain.validators.UserValidator;
import diana.repository.Repository;
import diana.repository.file.NetworkFileRepository;
import diana.repository.file.UserFileRepository;
import diana.service.UserService;
import diana.ui.ConsoleUI;

import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        Repository<String, User> userRepository = new UserFileRepository(Config.getProperties().getProperty("data.usersStorage"));
        UserValidator userValidator = new UserValidator();
        NetworkFileRepository network = new NetworkFileRepository(Config.getProperties().getProperty("data.usersStorage"),
                Config.getProperties().getProperty("data.friendshipsStorage"));
        UserService userService = new UserService(userRepository, userValidator, network);
        ConsoleUI console = new ConsoleUI(userService);

        console.run();
    }
}

