package socialnetwork.domain;
import socialnetwork.domain.exceptions.UserMissingException;
import socialnetwork.repository.Repository;

import java.util.*;

public class Network {
    private Map<User, Set<User>> network;
    private Repository<Set<String>, Friendship> friendshipRepository;
    private Repository<String, User> userRepository;

    public Network(Repository<String, User> userRepository, Repository<Set<String>, Friendship> friendshipRepository) {
        this.friendshipRepository = friendshipRepository;
        this.userRepository = userRepository;
        initializeNetwork();
    }
    public Network() {
        this.network = new HashMap<>();
    }

    private void initializeNetwork() {
        this.network = new HashMap<>();

        Map<String, User> users = userRepository.findAllMap();
        for(Map.Entry<String, User> user : users.entrySet()) {
            network.put(user.getValue(), new HashSet<>());
        }


        Iterable<Friendship> friendships = friendshipRepository.findAll();
        for(Friendship friendship : friendships) {
            User user1 = users.get(friendship.getUser1());
            User user2 = users.get(friendship.getUser2());
            network.get(user1).add(user2);
            network.get(user2).add(user1);
        }

    }

    @Override
    public String toString() {
        if(network.size() == 0) {
            return "Empty network!";
        }

        StringBuilder result = new StringBuilder();
        for(Map.Entry<User, Set<User>> entry : network.entrySet()) {
            result.append(entry.getKey().getId()).append(" ");
            if(entry.getValue().size() > 0) {
                result.append("is friend with ");
                for (User friend : entry.getValue()) {
                    result.append(friend.getId()).append(" ");
                }
            }
            else {
                result.append("does not have friends ");
            }
            result.append("\n");
        }

        return result.toString();
    }

    /**
     * Verifies if 2 users are friends
     * @param user1 User
     * @param user2 User
     * @throws UserMissingException if one of the users doesn't exist
     * @return true if user1 and user2 are friends
     */
    public boolean areFriends(User user1, User user2) {
        if(!network.containsKey(user1))
            throw new UserMissingException(user1.getId() + "doesn't exist.");
        if(!network.containsKey(user2))
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
        int friendships = 0;
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
                generatedNetwork.network.put(user, new HashSet<>());
                for(User friend : network.get(user)) {
                    if(!generatedNetwork.areFriends(user, friend)) {
                        generatedNetwork.network.get(user).add(friend);
                        generatedNetwork.network.get(friend).add(user);
                    }
                }
            }catch (Exception ignored){}
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
}