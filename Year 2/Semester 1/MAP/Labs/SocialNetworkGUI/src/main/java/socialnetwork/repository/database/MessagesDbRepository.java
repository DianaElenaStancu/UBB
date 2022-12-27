package socialnetwork.repository.database;

import socialnetwork.domain.Message;
import socialnetwork.domain.exceptions.EntityAlreadyExistsException;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

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

    @Override
    public Message findOne(String s) throws IllegalArgumentException, EntityMissingException {
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
     *
     * @param message
     * @return
     * @throws ValidationException
     * @throws IllegalArgumentException
     * @throws EntityAlreadyExistsException
     */
    @Override
    public Message save(Message message) throws ValidationException, IllegalArgumentException, EntityAlreadyExistsException {
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

    @Override
    public Message delete(String s) throws IllegalArgumentException {
        return null;
    }

    @Override
    public Message update(Message entity) throws IllegalArgumentException, ValidationException, EntityMissingException {
        return null;
    }

    /**
     *
     * @param resultSet
     * @return
     * @throws SQLException
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
     *
     * @param sender
     * @param receiver
     * @return
     */
    public Iterable<Message> findAllByUsers(String sender, String receiver) {
        Set<Message> messageSet = new LinkedHashSet<>();
        String sql = "select * from users where (sender = ? and receiver = ?) or (sender = ? and receiver = ?)";
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
     *
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
