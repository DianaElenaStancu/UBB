package socialnetwork.service;

import socialnetwork.domain.Network;
import socialnetwork.domain.User;
import socialnetwork.domain.exceptions.FriendshipMissingException;
import socialnetwork.domain.exceptions.UserAlreadyExistsException;
import socialnetwork.domain.exceptions.UserMissingException;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.repository.Repository;
import socialnetwork.repository.memory.InMemoryNetworkRepository;

public class UserService implements Service{
    private InMemoryNetworkRepository Network;
    private Repository<String, User> userRepository;
    private UserValidator userValidator;

    public UserService(Repository userRepository, UserValidator userValidator, InMemoryNetworkRepository network) {
        this.userRepository = userRepository;
        this.Network = network;
        this.userValidator = userValidator;
    }

    /**
     * Method that adds a user
     * @param username String
     * @param password String
     * @param email String
     * @param firstName String
     * @param lastName String
     * @throws UserAlreadyExistsException if the user already exists
     * @throws ValidationException if the given data is not valid for a user to be created
     */
    public void addUser(String username, String password, String email,
                        String firstName, String lastName)
            throws ValidationException {
        User user = new User(username, firstName, lastName, email, password);
        userValidator.validate(user);
        userRepository.save(user);
        Network.addUser(user);
    }


    /**
     * Method that removes a user based on its username
     * @param username String
     * @throws UserMissingException if the user does not exist
     */
    public void removeUser(String username) {
        User user = userRepository.findOne(username);
        userRepository.delete(user.getId());
        Network.removeUser(user);
    }

    /**
     * Method that creates the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws UserAlreadyExistsException if the 2 users are already friends
     * @throws UserMissingException if at least one of the usernames does not correspond to a user
     */
    public void addFriendship(String username1, String username2) {
        User user1 = userRepository.findOne(username1);
        User user2 = userRepository.findOne(username2);
        Network.createFriendship(user1, user2);
    }

    /**
     * Method that removes the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws FriendshipMissingException if the 2 users are not friends
     * @throws UserMissingException if at least one of the usernames does not correspond to a user
     */
    public void removeFriendShip(String username1, String username2) {
        User user1 = userRepository.findOne(username1);
        User user2 = userRepository.findOne(username2);
        Network.destroyFriendsShip(user1, user2);
    }

    /**
     * Method that returns the user with the given username
     * @param username String
     * @return User
     * @throws UserMissingException if there is not user with the given username
     */
    public User findUser(String username) {
        return this.userRepository.findOne(username);
    }

    /**
     * Method that returns the number of communities inside the network
     * @return Integer
     */
    public Integer numberOfCommunities() {
        return Network.numberOfCommunities();
    }

    /**
     * Method that returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        return Network.mostSocialCommunity();
    }


    /**
     * Method that clears the data
     */
    public void clear() {
        userRepository.clear();
        Network.clear();
    }
}
