package socialnetwork.repository.database;

import socialnetwork.domain.Message;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class MessagesDbRepository implements Repository<String, Message> {
    private final String url;
    private final String password;
    private final String username;

    /**
     * creates a repository that is connected to a database
     * @param url the url of the database
     * @param username for connecting to the database
     * @param password for connecting to the database
     */
    public MessagesDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * finds the message with a given id
     * @param id the id of the entity to be returned
     *           id must not be null
     * @return the message if exists, null otherwise
     * @throws IllegalArgumentException if username is null
     * @throws EntityMissingException if message with the given id doesn't exist
     */
    @Override
    public Message findOne(String id) throws IllegalArgumentException, EntityMissingException {
        if (username == null) {
            throw new IllegalArgumentException("Username cannot be null");
        }

        String sql = "select * from messages where id = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, Integer.parseInt(id));


            ResultSet resultSet = preparedStatement.executeQuery();
            if (!resultSet.next()) {
                throw new EntityMissingException("message with id: " + id + "doesn't exist");
            }

            return extractEntityFromResultSet(resultSet);
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return null;
    }

    @Override
    public Iterable<Message> findAll() {
        return null;
    }

    @Override
    public Map<String, Message> findAllMap() {
        return null;
    }

    /**
     * saves a message in the database
     * @param message Message
     * @return the saved message
     */
    @Override
    public Message save(Message message){
        String sql = "insert into  messages(text, timestamp, sender, receiver) values(?, ?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, message.getText());
            preparedStatement.setTimestamp(2, Timestamp.valueOf(message.getDate()));
            preparedStatement.setString(3, message.getSender());
            preparedStatement.setString(4, message.getReceiver());

            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return message;
    }

    /**
     * verifies if a Message with a given id exists
     * @param id the id of a Message
     * @return 1 if the entity exists, 0 otherwise
     */
    private boolean exists(String id) {
        try {
            findOne(id);
        } catch (EntityMissingException e) {
            return false;
        }
        return true;
    }

    /**
     * deletes a Messages with a given id
     * @param id
     *      id must be not null
     * @return the deleted Message
     */
    @Override
    public Message delete(String id) {

        if(!exists(id)) {
            return null;
        }
        Message message = findOne(id);
        String sql = "delete from messages where id = ?";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, Integer.parseInt(id));

            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return message;
    }

    //TODO
    @Override
    public Message update(Message entity) throws IllegalArgumentException, ValidationException, EntityMissingException {
        return null;
    }

    /**
     * extracts the entity from a Result Set
     * @param resultSet the resultSet obtained after a sql statement is executed
     * @return Message
     * @throws SQLException if the extraction is not finished successfully
     */
    private Message extractEntityFromResultSet(ResultSet resultSet) throws SQLException{
        String id = resultSet.getString("id");
        String text = resultSet.getString("text");
        LocalDateTime timestamp = resultSet.getTimestamp("timestamp").toLocalDateTime();
        String sender = resultSet.getString("sender");
        String receiver = resultSet.getString("receiver");

        return new Message(id, text, timestamp, sender, receiver);
    }

    /**
     * finds the conversation of two users
     * @param sender the person who sent messages
     * @param receiver the person who received messages
     * @return Iterable of Messages
     */
    public Iterable<Message> findAllByUsers(String sender, String receiver) {
        Set<Message> messageSet = new LinkedHashSet<>();
        String sql = "select * from messages where (sender = ? and receiver = ?) or (sender = ? and receiver = ?)";
        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, sender);
            preparedStatement.setString(2, receiver);
            preparedStatement.setString(3, receiver);
            preparedStatement.setString(4, sender);

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                Message message = extractEntityFromResultSet(resultSet);
                messageSet.add(message);
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return messageSet;
    }

    /**
     * clear the table messages from database
     */
    public void clear() {
        String sql = "delete from messages";

        try (Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }
}
