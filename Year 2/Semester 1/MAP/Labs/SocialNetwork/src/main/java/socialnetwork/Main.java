package socialnetwork;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.FriendshipValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.FriendshipsDbRepository;
import socialnetwork.repository.database.UserDbRepository;
//import socialnetwork.repository.file.FriendshipFileRepository;
//import socialnetwork.repository.file.UserFileRepository;
import socialnetwork.service.NetworkService;
import socialnetwork.ui.ConsoleUI;

import java.util.Set;

public class Main {
    public static void main(String[] args) {
        UserValidator userValidator = new UserValidator();
        FriendshipValidator friendshipValidator = new FriendshipValidator();
        //Repository<String, User> userRepository = new UserFileRepository(ApplicationContext.getPROPERTIES().getProperty("data.usersStorage"));//Config.getProperties().getProperty("data.usersStorage")
        Repository<String, User> userDbRepository = new UserDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));

        //Repository<Set<String>, Friendship> friendshipRepository = new FriendshipFileRepository(ApplicationContext.getPROPERTIES().getProperty("data.friendshipsStorage"));//Config.getProperties().getProperty("data.friendshipsStorage")
        Repository<Set<String>, Friendship> friendshipDbRepository = new FriendshipsDbRepository(ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl"),
                ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername"),
                ApplicationContext.getPROPERTIES().getProperty("data.databasePassword"));

        NetworkService networkService = new NetworkService(userDbRepository, userValidator, friendshipDbRepository, friendshipValidator);
        ConsoleUI console = new ConsoleUI(networkService);
        console.run();
    }
}
// jdbc:postgresql://localhost:5432/socialnetwork
/*
Operatii CRUD implementate
User: show all, save, delete, update, find, clear
Friendship: show all, create, destroy, find, clear
 */
/*
 * md5 hash
 */

