package socialnetwork.repository.database;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.exceptions.EntityAlreadyExistsException;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class FriendshipsDbRepository implements Repository<Set<String>, Friendship> {
    private final String url;
    private final String username;
    private final String password;

    /**
     * creates a repository that is connected to a database
     * @param url the url of the database
     * @param username for connecting to the database
     * @param password for connecting to the database
     */
    public FriendshipsDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * finds a friendship between user1 and user2
     * @param usernames a set consisting of two strings username1 and username2
     *           id must not be null
     * @return Friendship
     * @throws IllegalArgumentException if the username is null
     * @throws EntityMissingException if the usernames don't exist
     */
    @Override
    public Friendship findOne(Set<String> usernames) throws IllegalArgumentException, EntityMissingException {
        if (username == null) {
            throw new IllegalArgumentException("Username cannot be null");
        }

        List<String> usersList = new ArrayList<>(usernames);
        String firstUsername = usersList.get(0);
        String secondUsername = usersList.get(1);
        String sql = "select * from friendships where (first_user = ? and second_user = ?) or (first_user = ? and second_user = ?)";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, firstUsername);
            preparedStatement.setString(2, secondUsername);
            preparedStatement.setString(3, secondUsername);
            preparedStatement.setString(4, firstUsername);


            ResultSet resultSet = preparedStatement.executeQuery();
            if (!resultSet.next()) {
                throw new EntityMissingException(firstUsername + " and " + secondUsername + " are not friends :(");
            }

            return extractEntityFromResultSet(resultSet);
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return null;
    }

    /**
     *
     * @param resultSet
     * @return
     * @throws SQLException
     */
    private Friendship extractEntityFromResultSet(ResultSet resultSet) throws SQLException{
        String firstUsername = resultSet.getString("first_user");
        String secondUsername = resultSet.getString("second_user");
        LocalDateTime friendshipDate = resultSet.getTimestamp("date").toLocalDateTime();
        String friendshipStatus = resultSet.getString("status");

        return new Friendship(firstUsername, secondUsername, friendshipDate, friendshipStatus);
    }
    /**
     * Creates an Iterable<Friendship> with all friendships from the database
     * @return Iterable<Friendship>
     */
    @Override
    public Iterable<Friendship> findAll() {
        Set<Friendship> friendshipSet = new LinkedHashSet<>();
        String sql = "select * from friendships";
        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Friendship friendship = extractEntityFromResultSet(resultSet);
                friendshipSet.add(friendship);
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return friendshipSet;
    }

    /**
     * Creates an Map<Set<String>, Friendship> with all friendships from the database
     * @return Map<Set<String>, Friendship>
     */
    @Override
    public Map<Set<String>, Friendship> findAllMap() {
        Map<Set<String>, Friendship> friendshipMap = new HashMap<>();
        String sql = "select * from friendships";
        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Friendship friendship = extractEntityFromResultSet(resultSet);
                friendshipMap.put(friendship.getId(), friendship);
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return friendshipMap;
    }

    private boolean exists(Set<String> usernames) {
        try {
            findOne(usernames);
        } catch (EntityMissingException e) {
            return false;
        }
        return true;
    }

    /**
     * Adds a friendship in the database
     * @param friendship
     *         entity must be not null
     * @return the new created Friendship
     * @throws ValidationException if the friendship is not valid
     * @throws IllegalArgumentException .
     * @throws EntityAlreadyExistsException if the friendship is already in the database
     */
    @Override
    public Friendship save(Friendship friendship) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        if (exists(friendship.getId())) {
            throw new EntityAlreadyExistsException(friendship.getUser1() + " is already friend with " + friendship.getUser2());
        }
        String sql = "insert into friendships(first_user, second_user, date, status) values(?, ?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, friendship.getUser1());
            preparedStatement.setString(2, friendship.getUser2());
            preparedStatement.setTimestamp(3, Timestamp.valueOf(friendship.getFriendsFrom()));
            preparedStatement.setString(4, friendship.getStatus());


            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return findOne(friendship.getId());
    }

    /**
     * Deletes a friendship
     * @param usernames
     *      id must be not null
     * @return the friendship that was deleted
     * @throws IllegalArgumentException .
     */
    @Override
    public Friendship delete(Set<String> usernames) throws IllegalArgumentException {
        List<String> usersList = new ArrayList<>(usernames);
        String firstUsername = usersList.get(0);
        String secondUsername = usersList.get(1);

        if(!exists(usernames)) {
            throw new EntityMissingException(firstUsername + " is not friend with " + secondUsername);
        }

        Friendship friendship = findOne(usernames);
        String sql = "delete from friendships where (first_user = ? and second_user = ?) or (first_user = ? and second_user = ?)";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, firstUsername);
            preparedStatement.setString(2, secondUsername);
            preparedStatement.setString(3, secondUsername);
            preparedStatement.setString(4, firstUsername);


            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return friendship;
    }

    /**
     * updates a friendship
     * @param friendship
     *          entity must not be null
     * @return the updated friendship
     * @throws IllegalArgumentException .
     * @throws ValidationException if the new updated friendship is not valid
     * @throws EntityMissingException if the friendship is not valid
     */
    @Override
    public Friendship update(Friendship friendship) throws IllegalArgumentException, ValidationException, EntityMissingException {
        findOne(friendship.getId());

        String sql = "update friendships set date = ?, status = ? where (first_user = ? and second_user = ?) or (first_user = ? and second_user = ?)";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setTimestamp(1, Timestamp.valueOf(friendship.getFriendsFrom()));
            preparedStatement.setString(2, friendship.getStatus());
            preparedStatement.setString(3, friendship.getUser1());
            preparedStatement.setString(4, friendship.getUser2());
            preparedStatement.setString(5, friendship.getUser2());
            preparedStatement.setString(6, friendship.getUser1());

            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return friendship;
    }

    /**
     * clears the repo
     */
    @Override
    public void clear() {
        String sql = "delete from friendships";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }
}
