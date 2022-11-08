package elena.repository;

import elena.domain.User;

import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class UserDbRepo implements  Repository<Long, User>{
    private String urlDb;
    private String usernameDb;
    private String passwordDb;

    public UserDbRepo(String urlDb, String usernameDb, String passwordDb) {
        this.urlDb = urlDb;
        this.usernameDb = usernameDb;
        this.passwordDb = passwordDb;
    }

    @Override
    public User findOne(Long aLong) {
        return null;
    }

    @Override
    public Iterable<User> findAll() {
        Set<User> usersSet = new HashSet<>();
        //deschidem conexiune catre baza de date
        try(Connection connection = DriverManager.getConnection(urlDb, usernameDb, passwordDb);
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * from users");
            ResultSet resultSet = preparedStatement.executeQuery()) {
            while(resultSet.next()) {
                Long id = resultSet.getLong("id");
                String first_name = resultSet.getString("first_name");
                String last_name = resultSet.getString("last_name");
                User user = new User(first_name, last_name);
                user.setId(id);
                usersSet.add(user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return usersSet;
    }

    @Override
    public User save(User user) {
        String sql = "INSERT INTO users(first_name, last_name) VALUES(?, ?)";
        try(Connection connection = DriverManager.getConnection(urlDb, usernameDb, passwordDb);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)){
            preparedStatement.setString(1,user.getFirstName());
            preparedStatement.setString(1,user.getLastName());
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return user;
    }

    @Override
    public User delete(Long aLong) {
        return null;
    }

    @Override
    public User update(User user) {
        return null;
    }
}
