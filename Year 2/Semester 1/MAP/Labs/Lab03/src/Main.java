//import config.ApplicationContext;
//import config.Config;
import config.Config;
import domain.User;
import domain.validators.UserValidator;
import repository.Repository;
import repository.file.NetworkFileRepository;
import repository.file.UserFileRepository;
import service.UserService;
import ui.ConsoleUI;

public class Main {
    public static void main(String[] args) {
        //Config.getProperties().getProperty("usersStorage")
        Repository<String, User> userRepository = new UserFileRepository(Config.getProperties().getProperty("usersStorage"));
        UserValidator userValidator = new UserValidator();
        //Config.getProperties().getProperty("usersStorage")
        // Config.getProperties().getProperty("friendshipsStorage")
        NetworkFileRepository network = new NetworkFileRepository("/Users/dianastancu/Desktop/facultate/GIT/UBB/Year 2/Semester 1/MAP/Labs/Lab03/src/repository/database/usersStorage",
               "/Users/dianastancu/Desktop/facultate/GIT/UBB/Year 2/Semester 1/MAP/Labs/Lab03/src/repository/database/friendshipsStorage");
        UserService userService = new UserService(userRepository, userValidator, network);
        ConsoleUI console = new ConsoleUI(userService);

        console.run();
    }
}

