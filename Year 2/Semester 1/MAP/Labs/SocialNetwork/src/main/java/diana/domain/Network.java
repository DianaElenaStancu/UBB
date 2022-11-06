package diana.domain;

import diana.domain.exceptions.FriendshipAlreadyExistsException;
import diana.domain.exceptions.FriendshipMissingException;
import diana.domain.exceptions.UserAlreadyExistsException;
import diana.domain.exceptions.UserMissingException;

import java.util.*;

public class Network {
    private Map<User, Set<User>> network;

    public Network(Map<User, Set<User>> network) {
        if (network != null)
            this.network = network;
        else
            this.network = new HashMap<>();
    }

    public Network() {
        this.network = new HashMap<>();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == this) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass())
            return false;
        return Objects.equals(this.network, ((Network) obj).network);
    }

    @Override
    public String toString() {
        if(network.size() == 0) {
            return "Empty network!";
        }

        String result = "";
        for(Map.Entry<User, Set<User>> entry : network.entrySet()) {
            result += entry.getKey().getId() + " ";
            if(entry.getValue().size() > 0) {
                result += "is friend with ";
                for (User friend : entry.getValue()) {
                    result += friend.getId() + " ";
                }
            }
            else {
                result += "does not have friends ";
            }
            result += "\n";
        }

        return result;
    }

    /**
     * Removes a user from the network
     * @param user  User
     * @throws UserAlreadyExistsException if the user already exists
     */
    public void addUser(User user) {
        if (!network.containsKey(user)) {
            network.put(user, new HashSet<>());
            return;
        }
        throw new UserAlreadyExistsException(user.getId() + "already exists.");
    }


    /**
     * Removes a user from the network
     * @param user  User
     * @throws UserMissingException if the user doesn't exist
     */
    public void removeUser(User user) {
        if (network.containsKey(user)) {
            network.remove(user);
            for(Map.Entry<User, Set<User>> entries : network.entrySet()) {
                entries.getValue().remove(user);
            }
            return;
        }
        throw new UserMissingException(user.getId() + "doesn't exist.");
    }

    /**
     * Creates a friendship in the network
     * @param user1  User
     * @param user2  User
     * @throws UserMissingException if one of the users doesn't exist
     * @throws FriendshipAlreadyExistsException if user1 and user2 are already friends
     */
    public void createFriendship(User user1, User user2) {
        if (user1.equals(user2))
            return;
        if (!network.containsKey(user1)) {
            throw new UserMissingException(user1.getId() + "doesn't exist.");
        }
        if (!network.containsKey(user2)) {
            throw new UserMissingException(user2.getId() + "doesn't exist.");
        }
        if (areFriends(user1, user2)) {
            throw new FriendshipAlreadyExistsException(user1.getId() + "is already friend with" + user2.getId());
        }

        network.get(user1).add(user2);
        network.get(user2).add(user1);
    }

    /**
     * Destroys a friendship in the network
     * @param user1  User
     * @param user2  User
     * @throws UserMissingException if one of the users doesn't exist
     * @throws FriendshipMissingException if user1 and user2 are not friends
     */
    public void destroyFriendship(User user1, User user2) {
        if (!existUser(user1)) {
            throw new UserMissingException(user1.getId() + "doesn't exist.");
        }
        if (!existUser(user2)) {
            throw new UserMissingException(user2.getId() + "doesn't exist.");
        }
        if (!areFriends(user1, user2)) {
            throw new FriendshipMissingException(user1.getId() + "is not a friend with" + user2.getId());
        }

        network.get(user1).remove(user2);
        network.get(user2).remove(user1);
    }

    /**
     * Verifies if a user exists
     * @param user User
     * @return true if the user exists
     */
    public boolean existUser(User user) {
        return network.containsKey(user);
    }

    /**
     * Verifies if 2 users are friends
     * @param user1 User
     * @param user2 User
     * @throws UserMissingException if one of the users doesn't exist
     * @return true if user1 and user2 are friends
     */
    public boolean areFriends(User user1, User user2) {
        if(!existUser(user1))
            throw new UserMissingException(user1.getId() + "doesn't exist.");
        if(!existUser(user2))
            throw new UserMissingException(user2.getId() + "doesn't exist");
        return network.get(user1).contains(user2);
    }

    /**
     * Applies dfs for finding all the members of a social community
     * @param user User
     * @param friendsOfUser HashSet<User>
     */
    private void dfs(User user, HashSet<User> friendsOfUser) {
        for (User friend : network.get(user)) {
            if (!friendsOfUser.contains(friend)) {
                friendsOfUser.add(friend);
                dfs(friend, friendsOfUser);
            }
        }
    }

    /**
     * Calculates the number of the communities
     * @return Integer number of communities
     */
    public Integer numberOfCommunities() {
        Integer result = 0;

        HashSet<User> visitedUsers = new HashSet<>();
        for(User user : network.keySet()) {
            if (!visitedUsers.contains(user)) {
                HashSet<User> friendsOfUser = new HashSet<>();
                ++result;
                dfs(user, friendsOfUser);
                visitedUsers.addAll(friendsOfUser);
            }
        }
        return result;
    }

    /**
     * returns the number of friendships in a given network
     * @param network Network
     * @return Integer
     */
    private static Integer numberOfFriendships(Network network) {
        Integer friendships = 0;
        for(User user : network.network.keySet()) {
            friendships += network.network.get(user).size();
        }
        return friendships / 2;
    }

    /**
     * generates the subnetwork consisting of the users that are in the users Set
     * @param users Set<User>
     * @return Network
     */
    private Network generateSubNetwork(Set<User> users) {
        Network generatedNetwork = new Network();
        for(User user : users) {
            try{
                generatedNetwork.addUser(user);
                for(User friend : network.get(user)) {
                    if(!generatedNetwork.areFriends(user, friend)) {
                        generatedNetwork.createFriendship(user, friend);
                    }
                }
            }catch (Exception exception){};
        }

        return generatedNetwork;
    }

    /**
     * returns the most social community
     * @return Network
     */
    public Network mostSocialCommunity() {
        Set<User> visitedUsers = new HashSet<>();
        Network mostSocialCommunity = new Network();
        for(User user : network.keySet()) {
            if(!visitedUsers.contains(user)) {
                HashSet<User> componentUsers = new HashSet<>();
                dfs(user, componentUsers);
                visitedUsers.addAll(componentUsers);

                Network componentNetwork = generateSubNetwork(componentUsers);
                if(numberOfFriendships(componentNetwork) > numberOfFriendships(mostSocialCommunity)) {
                    mostSocialCommunity = componentNetwork;
                }
            }
        }

        return mostSocialCommunity;
    }

    public void clear() {
        network.clear();
    }
}
