package socialnetwork;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.FriendshipValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.repository.Repository;
import socialnetwork.repository.file.FriendshipFileRepository;
import socialnetwork.repository.file.UserFileRepository;
import socialnetwork.service.NetworkService;
import socialnetwork.ui.ConsoleUI;

import java.util.Set;

public class Main {
    public static void main(String[] args) {
        UserValidator userValidator = new UserValidator();
        FriendshipValidator friendshipValidator = new FriendshipValidator();
        Repository<String, User> userRepository = new UserFileRepository(ApplicationContext.getPROPERTIES().getProperty("data.usersStorage"));//Config.getProperties().getProperty("data.usersStorage")
        Repository<Set<String>, Friendship> friendshipRepository = new FriendshipFileRepository(ApplicationContext.getPROPERTIES().getProperty("data.friendshipsStorage"));//Config.getProperties().getProperty("data.friendshipsStorage")
        NetworkService networkService = new NetworkService(userRepository, userValidator, friendshipRepository, friendshipValidator);
        ConsoleUI console = new ConsoleUI(networkService);
        console.run();
    }
}

/*
Operatii CRUD implementate
User: show all, save, delete, update, find, clear
Friendship: show all, create, destroy, find, clear
 */

