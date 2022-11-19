package socialnetwork.repository.file;

import socialnetwork.domain.User;

import java.util.List;

public class UserFileRepository extends AbstractFileRepository<String, User> {

    public UserFileRepository(String fileName) {
        super(fileName);
    }

    @Override
    public User extractEntity(List<String> attributes) {
        return new User(attributes.get(0), attributes.get(1), attributes.get(2), attributes.get(3), attributes.get(4));
    }

    @Override
    protected String createEntityAsString(User entity) {
        return entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName() + ";" + entity.getEmail() + ";" + entity.getPassword() + "\n";
    }
}
