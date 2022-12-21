package socialnetwork.service;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.exceptions.EntityAlreadyExistsException;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.exceptions.FriendshipWithYourselfException;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.domain.validators.Validator;
import socialnetwork.repository.Repository;

import java.time.LocalDateTime;
import java.util.*;

public class NetworkService implements Service {
    private final Repository<String, User> userRepository;
    private final Repository<Set<String>, Friendship> friendshipRepository;
    private final Validator<User> userValidator;
    private final Validator<Friendship> friendshipValidator;

    /**
     * Creates a service for users
     * @param userRepository - a repository of users
     * @param userValidator - a validator for users
     * @param  friendshipRepository - a repository of friendships
     * @param friendshipValidator - a validator for users
     */
    public NetworkService(Repository<String, User> userRepository, Validator<User> userValidator,
                          Repository<Set<String>, Friendship> friendshipRepository, Validator<Friendship> friendshipValidator) {
        this.userRepository = userRepository;
        this.userValidator = userValidator;
        this.friendshipRepository = friendshipRepository;
        this.friendshipValidator = friendshipValidator;
    }

    /**
     * Creates and validates a User
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
            throws EntityAlreadyExistsException, ValidationException {
        User user = new User(username, firstName, lastName, email, password);
        userValidator.validate(user);
        userRepository.save(user);
    }

    /**
     * Modifies an existing User
     * @param username String
     * @param password String
     * @param email String
     * @param firstName String
     * @param lastName String
     * @throws EntityMissingException if the user does not exist
     * @throws ValidationException if the given data is not valid for a user to be created
     */
    public void updateUser(String username, String firstName, String lastName, String email, String password) throws EntityMissingException, ValidationException{
        User user = new User(username, firstName, lastName, email, password);
        userValidator.validate(user);
        userRepository.update(user);
    }


    /**
     * Removes a User based on its username
     * @param user String
     * @throws EntityMissingException if the user does not exist
     */
    public void removeUser(String user) throws EntityMissingException{
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

    /**
     * Creates a set with the friends of a given User
     * @param username String the id of the User
     * @return an Iterable<User> with all the users' friends
     */
    public Iterable<User> showUserFriends(String username) {
        Set<User> friends = new HashSet<>();
        Iterable<User> users = userRepository.findAll();
        for (User friend : users) {
            Friendship friendship = new Friendship(friend.getId(), username);
            try {
                friendshipRepository.findOne(friendship.getId());
                friends.add(friend);
            }  catch(Exception ignored){
            }
        }
        return friends;
    }

    /**
     * Creates the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws EntityAlreadyExistsException if the 2 users are already friends
     * @throws ValidationException if the both usernames are the same
     * @throws EntityMissingException if at least one of the usernames does not correspond to a user
     */
    public void addFriendship(String username1, String username2, String status) throws EntityAlreadyExistsException, ValidationException, EntityMissingException {
        userRepository.findOne(username1);
        userRepository.findOne(username2);
        Friendship friendship = new Friendship(username1, username2, status);
        friendshipValidator.validate(friendship);
        friendshipRepository.save(friendship);
    }

    /**
     * Removes the friendship between 2 users based on their usernames
     * @param username1 String
     * @param username2 String
     * @throws EntityMissingException if the 2 users are not friends
     * @throws EntityMissingException if at least one of the usernames does not correspond to a user
     */
    public void removeFriendship(String username1, String username2) throws  EntityMissingException{
        friendshipRepository.delete(new TreeSet<>(Arrays.asList(username1, username2)));
    }

    /**
     * Modifies the friendship date of a friendship
     * @param username1 username of the first user
     * @param username2 username of the second user
     * @param friendshipDate the new date of the friendship
     * @throws ValidationException if the given date is in the future
     * @throws EntityMissingException if at least one of the usernames does not correspond to a user
     */
    public void updateFriendship(String username1, String username2, LocalDateTime friendshipDate, String status) throws ValidationException, EntityMissingException{
        userRepository.findOne(username1);
        userRepository.findOne(username2);

        Friendship friendship = new Friendship(username1, username2, friendshipDate, status);
        friendshipValidator.validate(friendship);
        friendshipRepository.update(friendship);
    }

    /**
     * Finds the user based on its username
     * @param username String
     * @return User
     * @throws EntityMissingException if there is no user with the given username
     */
    public User findUser(String username) throws EntityMissingException {
        return this.userRepository.findOne(username);
    }

    /**
     * Finds the friendship between the given usernames
     * @param username1 username of the first user
     * @param username2 username of the first user
     * @return Friendship
     * @throws EntityMissingException if there is no friendship between the given users
     * @throws FriendshipWithYourselfException if the username1 and username2 are the same
     */
    public Friendship findFriendship(String username1, String username2) throws EntityMissingException, FriendshipWithYourselfException {
        if (!Objects.equals(username1, username2))
            return this.friendshipRepository.findOne(new TreeSet<>(Arrays.asList(username1, username2)));
        else
            throw new FriendshipWithYourselfException("You can't be friend with you!");
    }

    public Iterable<User> getAllUsers() {
        return userRepository.findAll();
    }

    /**
     * Returns the status of a friendship
     * @param username1 the username of the first User
     * @param username2 the username of the second User
     * @return the status of a friendship
     * it can be:
     *          accepted by username1/username2
     *          request sent by username1/username2
     *          not friends
     */
    public String getStatusOfFriendship(String username1, String username2) {
        String status;
        try {
            Friendship friendship = this.findFriendship(username1, username2);
            if (Objects.equals(friendship.getStatus(), "accepted")) {
                status = "accepted by " + friendship.getUser2();
            } else {
                status = "request sent by " + friendship.getUser1();
            }
        } catch (EntityMissingException entityMissingException) {
            status = "not friends";
        }
        return status;
    }

    /**
     * Verifies if the password matches the users' password
     * @param user User
     * @param password a String given by the user
     * @return true if the password given by the user is equal with the password of the user
     */
    public boolean verifyCredentials(User user, String password) {
        return Objects.equals(user.getPassword(), password);
    }


    /**
     * Clears the data from the database
     */
    public void clear() {
        friendshipRepository.clear();
        userRepository.clear();
    }
}