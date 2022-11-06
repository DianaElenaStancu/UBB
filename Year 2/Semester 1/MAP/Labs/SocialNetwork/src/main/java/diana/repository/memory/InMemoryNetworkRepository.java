package diana.repository.memory;

import diana.domain.Network;
import diana.domain.User;
import diana.domain.exceptions.EntityAlreadyExistsException;
import diana.domain.exceptions.EntityMissingException;

public class InMemoryNetworkRepository {
    private Network network;

    /**
     * Constructor for the AllNetwork class
     */
    public InMemoryNetworkRepository() {
        network = new Network();
    }

    /**
     * Method that adds a user to the network
     * @param user User
     * @throws EntityAlreadyExistsException if the user is already in the network
     */
    public void addUser(User user) {
        this.network.addUser(user);
    }

    /**
     * Method that removes a user from the network
     * @param user User
     * @throws EntityMissingException if the user does not exist in the network
     */
    public void removeUser(User user) {
        this.network.removeUser(user);
    }

    /**
     * Method that adds a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws EntityMissingException if at least one of the user does not exist in the network
     * @throws EntityAlreadyExistsException if there is already a friendship between the users
     */
    public void createFriendship(User user1, User user2) {
        this.network.createFriendship(user1, user2);
    }

    /**
     * Method that removes a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws EntityMissingException if at least one of the user does not exist in the network
     * @throws EntityMissingException if there is not friendship between the users with the given usernames
     */
    public void destroyFriendsShip(User user1, User user2) {
        network.destroyFriendship(user1, user2);
    }

    /**
     * Method that tests if 2 users are friends
     * @param user1 User
     * @param user2 User
     * @return true if they are friends and false otherwise
     * @throws EntityMissingException if at least one of the users does not exist
     */
    public boolean areFriends(User user1, User user2) {
        return network.areFriends(user1, user2);
    }

    /**
     * Method that returns the number of communities inside the network
     * @return Integer
     */
    public Integer numberOfCommunities() {
        return network.numberOfCommunities();
    }

    /**
     * Method that returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        return network.mostSocialCommunity();
    }


    /**
     * Method that clears the network
     */
    public void clear() {
        network.clear();
    }
}
