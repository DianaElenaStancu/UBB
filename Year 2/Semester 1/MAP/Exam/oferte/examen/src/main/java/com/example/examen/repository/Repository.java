package com.example.examen.repository;

import com.example.examen.domain.Entity;
import com.example.examen.domain.exceptions.EntityAlreadyExistsException;
import com.example.examen.domain.exceptions.EntityMissingException;
import com.example.examen.domain.validators.ValidationException;

//public class UserDbRepository implements Repository<String, User> {
//    private final  String url;
//    private final String username;
//    private final String password;
//
//    /**
//     * creates a user repository
//     * @param url of the database
//     * @param password for connecting to the database
//     * @param username for connecting to the database
//     */
//    public UserDbRepository(String url, String username, String password) {
//        this.url = url;
//        this.username = username;
//        this.password = password;
//    }
//
//public TablesDbRepository() {
//        this.url = ApplicationContext.getPROPERTIES().getProperty("data.databaseUrl");
//        this.username = ApplicationContext.getPROPERTIES().getProperty("data.databaseUsername");
//        this.password = ApplicationContext.getPROPERTIES().getProperty("data.databasePassword");
//        }
//    /**
//     * extracts a user form a resultSet
//     * @param resultSet - result of a query
//     * @return the User from the resultSet
//     * @throws SQLException if the result cannot be converted to entity
//     */
//    private User extractEntityFromResultSet(ResultSet resultSet) throws SQLException {
//        String username = resultSet.getString("username");
//        String first_name = resultSet.getString("first_name");
//        String last_name = resultSet.getString("last_name");
//        String email = resultSet.getString("email");
//        String password = resultSet.getString("password");
//
//        return new User(username, first_name, last_name, email, password);
//    }
//
//    /**
//     * Searches for a user
//     * @param username the id of the entity to be returned
//     *           id must not be null
//     * @return User the user that was found
//     * @throws IllegalArgumentException if the username is null
//     * @throws EntityMissingException if the user doesn't exist
//     */
//    @Override
//    public User findOne(String username) throws IllegalArgumentException, EntityMissingException {
//        if (username == null) {
//            throw new IllegalArgumentException("Username for the database is null!");
//        }
//
//        String sql = "select * from users where username = ?";
//        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
//             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
//
//            preparedStatement.setString(1, username);
//            ResultSet resultSet = preparedStatement.executeQuery();
//
//            if(!resultSet.next()) {
//                throw new EntityMissingException(username + " does not exist!");
//            }
//
//            return extractEntityFromResultSet(resultSet);
//
//        } catch (SQLException sqlException) {
//            sqlException.printStackTrace();
//        }
//
//        return null;
//    }
//
//    /**
//     * Creates an Iterable<User> with all users from the database
//     * @return Iterable<User>
//     */
//    @Override
//    public Iterable<User> findAll() {
//        Set<User> users = new HashSet<>();
//        String sql = "select * from users";
//        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
//             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
//
//            ResultSet resultSet = preparedStatement.executeQuery();
//
//            while(resultSet.next()) {
//                User user  = extractEntityFromResultSet(resultSet);
//                users.add(user);
//            }
//
//        } catch (SQLException sqlException) {
//            sqlException.printStackTrace();
//        }
//
//        return users;
//    }
//
//    /**
//     * Creates an Map<String,User> with all users from the database
//     * @return Map<String,User>
//     */
//    @Override
//    public Map<String, User> findAllMap() {
//        Map<String, User> users = new HashMap<>();
//        String sql = "select * from users";
//        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
//             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
//
//            ResultSet resultSet = preparedStatement.executeQuery();
//
//            while(resultSet.next()) {
//                User user  = extractEntityFromResultSet(resultSet);
//                users.put(user.getId(), user);
//            }
//
//        } catch (SQLException sqlException) {
//            sqlException.printStackTrace();
//        }
//
//        return users;
//    }
//
//    /**
//     *
//     */
//    private boolean userExists(String username) {
//        try {
//            findOne(username);
//        } catch (EntityMissingException e) {
//            return false;
//        }
//        return true;
//    }
//
//    /**
//     * Saves a new user into database
//     * @param user
//     *         entity must be not null
//     * @return user that was added
//     * @throws ValidationException if the user is not valid
//     * @throws IllegalArgumentException .
//     * @throws EntityAlreadyExistsException if the entity is already in the database
//     */
//    @Override
//    public User save(User user) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
//        if (userExists(user.getId())) {
//            throw new EntityAlreadyExistsException(user.getId() + " already exists!");
//        }
//
//        String sql = "insert into users values (?, ?, ?, ?, ?)";
//
//        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
//             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
//            preparedStatement.setString(1, user.getId());
//            preparedStatement.setString(2, user.getFirstName());
//            preparedStatement.setString(3, user.getLastName());
//            preparedStatement.setString(4, user.getEmail());
//            preparedStatement.setString(5, user.getPassword());
//            preparedStatement.executeUpdate();
//        } catch (SQLException sqlException) {
//            sqlException.printStackTrace();
//        }
//
//        return user;
//    }
//
//    /**
//     * Deletes a user from the database
//     * @param username
//     *      id must be not null
//     * @return user with the given username
//     * @throws IllegalArgumentException .
//     */
//    @Override
//    public User delete(String username) throws IllegalArgumentException {
//        User user = findOne(username);
//
//        String sql = "delete from users where username = ?";
//
//        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
//             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
//            preparedStatement.setString(1, username);
//
//            preparedStatement.executeUpdate();
//        } catch (SQLException sqlException) {
//            sqlException.printStackTrace();
//        }
//
//        return user;
//    }
//
//
//    /**
//     * updates a user from the database
//     * @param user
//     *          entity must not be null
//     * @return User the user updated
//     * @throws IllegalArgumentException .
//     * @throws ValidationException .
//     * @throws EntityMissingException if the user that wants to be updated is not in the database.
//     */
//    @Override
//    public User update(User user) throws IllegalArgumentException, ValidationException, EntityMissingException {
//        findOne(user.getId());
//
//        String sql = "update users set first_name = ?, last_name = ?, email = ?, password = ? WHERE username = ?";
//
//        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
//             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
//            preparedStatement.setString(1, user.getFirstName());
//            preparedStatement.setString(2, user.getLastName());
//            preparedStatement.setString(3, user.getEmail());
//            preparedStatement.setString(4, user.getPassword());
//
//            preparedStatement.setString(5, user.getId());
//
//            preparedStatement.executeUpdate();
//        } catch (SQLException sqlException) {
//            sqlException.printStackTrace();
//        }
//
//        return user;
//    }
//
//    @Override
//    public void clear() {
//        String sql = "delete from users";
//
//        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
//             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
//            preparedStatement.executeUpdate();
//        } catch (SQLException sqlException) {
//            sqlException.printStackTrace();
//        }
//    }
//}


/**
 * CRUD operations repository interface
 *
 * @param <ID> type E must have an attribute of type ID
 * @param <E>  type of entities saved in repository
 */

public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Returns the entity that has the given id
     *
     * @param id the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     * or null - if there is no entity with the given id
     * @throws IllegalArgumentException if id is null.
     * @throws EntityMissingException   if the entity doesn't exist.
     */
    E findOne(ID id) throws IllegalArgumentException, EntityMissingException;

    /**
     * @return Iterable<E> with all entities
     */
    Iterable<E> findAll();

    /*

     @return Map <ID, E> with all entities

    Map<ID, E> findAllMap();
    */
    /**
     * Adds an entity in repository
     *
     * @param entity entity must be not null
     * @return null- if the given entity is saved
     * otherwise returns the entity (id already exists)
     * @throws ValidationException          if the entity is not valid
     * @throws IllegalArgumentException     if the given entity is null.     *
     * @throws EntityAlreadyExistsException if the entity is already in repository
     */
    E save(E entity) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException;


    /**
     * Removes the entity with the specified id
     *
     * @param id id must be not null
     * @return the removed entity or null if there is no entity with the given id
     * @throws IllegalArgumentException if the given id is null.
     * @throws EntityMissingException   if there is no user with the given id.
     */
    E delete(ID id) throws IllegalArgumentException;

    /**
     * Updates the entity with the given id
     *
     * @param entity entity must not be null
     * @return null - if the entity is updated,
     * otherwise  returns the entity  - (e.g id does not exist).
     * @throws IllegalArgumentException if the given entity is null.
     * @throws ValidationException      if the entity is not valid.
     * @throws EntityMissingException   if the entity doesn't exist.
     */
    E update(E entity) throws IllegalArgumentException, ValidationException, EntityMissingException;

    /**
     * Clears the repository
     */
    void clear();
}

