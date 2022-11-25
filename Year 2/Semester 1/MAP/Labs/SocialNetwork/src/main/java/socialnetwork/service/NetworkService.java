package socialnetwork.service;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.Network;
import socialnetwork.domain.User;
import socialnetwork.domain.exceptions.EntityAlreadyExistsException;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.domain.validators.Validator;
import socialnetwork.repository.Repository;

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class NetworkService implements Service {
    private Repository<String, User> userRepository;
    private Repository<Set<String>, Friendship> friendshipRepository;
    private Validator userValidator;
    private Validator friendshipValidator;

    /**
     * Constructor for creating a service for users
     * @param userRepository - a repository of users
     * @param userValidator - a validator for users
     * @param  friendshipRepository - a repository of friendships
     * @param friendshipValidator - a validator for users
     */
    public NetworkService(Repository userRepository, Validator userValidator,
                          Repository friendshipRepository, Validator friendshipValidator) {
        this.userRepository = userRepository;
        this.userValidator = userValidator;
        this.friendshipRepository = friendshipRepository;
        this.friendshipValidator = friendshipValidator;
    }

    /**
     * Method that adds a user
     * @param username String
     * @param password String
     * @param email String
     * @param firstName String
     * @param lastName String
     * @throws EntityAlreadyExistsException if the user already exists
     * @throws ValidationException if the given data is not valid for a user to be created
     */
    public void addUser(String username,
                        String firstName, String lastName, String email, String password)
            throws ValidationException {
        User user = new User(username, firstName, lastName, email, password);
        userValidator.validate(user);
        userRepository.save(user);
    }

    /**
     * Method that modifies a user
     * @param username String
     * @param password String
     * @param email String
     * @param firstName String
     * @param lastName String
     * @throws EntityMissingException if the user does not exist
     * @throws ValidationException if the given data is not valid for a user to be created
     */
    public void updateUser(String username, String firstName, String lastName, String email, String password) {
        User user = new User(username, firstName, lastName, email, password);
        userValidator.validate(user);
        userRepository.update(user);
    }


    /**
     * Method that removes a user based on its username
     * @param user String
     * @throws EntityMissingException if the user does not exist
     */
    public void removeUser(String user) {
        userRepository.findOne(user);

        Iterable<User> users = userRepository.findAll();
        for (User friend : users) {
            Friendship friendship = new Friendship(friend.getId(), user);
            try {
                friendshipRepository.delete(friendship.getId());
            } catch(Exception ignored){
            }
        }

        userRepository.delete(user);
    }

    public Iterable<User> showUserFriends(User user) {
        Set<User> friends = new HashSet<>();
        Iterable<User> users = userRepository.findAll();
        for (User friend : users) {
            Friendship friendship = new Friendship(friend.getId(), user.getId());
            try {
                friendshipRepository.findOne(friendship.getId());
                friends.add(friend);
            }  catch(Exception ignored){
            }
        }
        return friends;
    }

    /**
     * Method that creates the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws EntityAlreadyExistsException if the 2 users are already friends
     * @throws ValidationException if the both usernames are the same
     * @throws EntityMissingException if at least one of the usernames does not correspond to a user
     */
    public void addFriendship(String username1, String username2) {
        userRepository.findOne(username1);
        userRepository.findOne(username2);
        Friendship friendship = new Friendship(username1, username2);
        friendshipValidator.validate(friendship);
        friendshipRepository.save(friendship);
    }

    /**
     * Method that removes the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws EntityMissingException if the 2 users are not friends
     * @throws EntityMissingException if at least one of the usernames does not correspond to a user
     */
    public void removeFriendship(String username1, String username2) {
        User user1 = userRepository.findOne(username1);
        User user2 = userRepository.findOne(username2);
        friendshipRepository.delete(new TreeSet<>(Arrays.asList(username1, username2)));
    }

    /**
     * Method that modifies the friendship date of a friendship
     * @param username1 username of the first user
     * @param username2 username of the second user
     * @param friendshipDate the new date of the friendship
     * @throws ValidationException if the given date is in the future
     * @throws EntityMissingException if at least one of the usernames does not correspond to a user
     */
    public void updateFriendship(String username1, String username2, LocalDateTime friendshipDate) {
        userRepository.findOne(username1);
        userRepository.findOne(username2);

        Friendship friendship = new Friendship(username1, username2, friendshipDate);
        friendshipValidator.validate(friendship);
        friendshipRepository.update(friendship);
    }

    /**
     * Method that returns the user with the given username
     * @param username String
     * @return User
     * @throws EntityMissingException if there is not user with the given username
     */
    public User findUser(String username) {
        return this.userRepository.findOne(username);
    }

    /**
     * Method that returns the friendship between the given usernames
     * @param username1 username of the first user
     * @param username2 username of the first user
     * @return Friendship
     * @throws EntityMissingException if there is no friendship between the given users
     */
    public Friendship findFriendship(String username1, String username2) {
        return this.friendshipRepository.findOne(new TreeSet<>(Arrays.asList(username1, username2)));
    }

    /**
     * Method that returns the number of communities inside the network
     * @return Integer
     */
    public Integer numberOfCommunities() {
        Network network = new Network(this.userRepository.findAllMap(), this.friendshipRepository.findAll());
        return network.numberOfCommunities();
    }

    /**
     * Method that returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        Network network = new Network(this.userRepository.findAllMap(), this.friendshipRepository.findAll());
        return network.mostSocialCommunity();
    }

    public Iterable<User> getAllUsers() {
        return userRepository.findAll();
    }

    public Iterable<Friendship> getAllFriendships() {
        return friendshipRepository.findAll();
    }

    /**
     * Method that clears the data
     */
    public void clear() {
        friendshipRepository.clear();
        userRepository.clear();
    }
}