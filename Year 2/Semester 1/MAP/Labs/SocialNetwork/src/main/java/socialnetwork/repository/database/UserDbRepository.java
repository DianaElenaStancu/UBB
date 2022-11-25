package socialnetwork.repository.database;

import socialnetwork.domain.User;
import socialnetwork.domain.exceptions.EntityAlreadyExistsException;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class UserDbRepository implements Repository<String, User> {
    private String url;
    private String username;
    private String password;

    /**
     * creates a user repository
     * @param url of the database
     * @param password for connecting to the database
     * @param username for connecting to the database
     */
    public UserDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * extracts a user form a resultSet
     * @param resultSet - result of a query
     * @return the User from the resultSet
     * @throws SQLException
     */
    private User extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
        String username = resultSet.getString("username");
        String first_name = resultSet.getString("first_name");
        String last_name = resultSet.getString("last_name");
        String email = resultSet.getString("email");
        String password = resultSet.getString("password");

        return new User(username, first_name, last_name, email, password);
    }

    /**
     * Searches for a user
     * @param username the id of the entity to be returned
     *           id must not be null
     * @return
     * @throws IllegalArgumentException
     * @throws EntityMissingException
     */
    @Override
    public User findOne(String username) throws IllegalArgumentException, EntityMissingException {
        if (username == null) {
            throw new IllegalArgumentException("Username for the database is null!");
        }

        String sql = "select * from users where username = ?";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();

            if(!resultSet.next()) {
                throw new EntityMissingException(username + " does not exist!");
            }

            return extractEntityFromResultSet(resultSet);

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return null;
    }

    /**
     * Creates an Iterable<User> with all users from the database
     * @return Iterable<User>
     */
    @Override
    public Iterable<User> findAll() {
        Set<User> users = new HashSet<>();
        String sql = "select * from users";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while(resultSet.next()) {
                User user  = extractEntityFromResultSet(resultSet);
                users.add(user);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return users;
    }

    /**
     * Creates an Map<String,User> with all users from the database
     * @return Map<String,User>
     */
    @Override
    public Map<String, User> findAllMap() {
        Map<String, User> users = new HashMap<>();
        String sql = "select * from users";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while(resultSet.next()) {
                User user  = extractEntityFromResultSet(resultSet);
                users.put(user.getId(), user);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return users;
    }

    /**
     *
     */
    private boolean userExists(String username) {
        try {
            findOne(username);
        } catch (EntityMissingException e) {
            return false;
        }
        return true;
    }

    /**
     * Saves a new user into database
     * @param user
     *         entity must be not null
     * @return user that was added
     * @throws ValidationException
     * @throws IllegalArgumentException
     * @throws EntityAlreadyExistsException
     */
    @Override
    public User save(User user) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
        if (userExists(user.getId())) {
            throw new EntityAlreadyExistsException(user.getId() + " already exists!");
        }

        String sql = "insert into users values (?, ?, ?, ?, ?)";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, user.getId());
            preparedStatement.setString(2, user.getFirstName());
            preparedStatement.setString(3, user.getLastName());
            preparedStatement.setString(4, user.getEmail());
            preparedStatement.setString(5, user.getPassword());
            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return user;
    }

    /**
     * Deletes a user from the database
     * @param username
     *      id must be not null
     * @return user with the given username
     * @throws IllegalArgumentException
     */
    @Override
    public User delete(String username) throws IllegalArgumentException {
        User user = findOne(username);

        String sql = "delete from users where username = ?";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, username);

            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return user;
    }


    /**
     * updates a user from the database
     * @param user
     *          entity must not be null
     * @return User the user updated
     * @throws IllegalArgumentException
     * @throws ValidationException
     * @throws EntityMissingException
     */
    @Override
    public User update(User user) throws IllegalArgumentException, ValidationException, EntityMissingException {
        findOne(user.getId());

        String sql = "update users set first_name = ?, last_name = ?, email = ?, password = ? WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, user.getFirstName());
            preparedStatement.setString(2, user.getLastName());
            preparedStatement.setString(3, user.getEmail());
            preparedStatement.setString(4, user.getPassword());

            preparedStatement.setString(5, user.getId());

            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return user;
    }

    @Override
    public void clear() {
        String sql = "delete from users";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }
}
