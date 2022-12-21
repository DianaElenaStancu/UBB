package socialnetwork.repository.file;

import socialnetwork.domain.Friendship;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import static socialnetwork.constants.DateTime.DATATIME_FORMATTER;

public class FriendshipFileRepository extends AbstractFileRepository<Set<String>, Friendship> {


    /**
     * Creates a repository with persistence in file
     * @param filename - the path where the data is stored
     */
    public FriendshipFileRepository(String filename) {
        super(filename);
    }

    /**
     * Converts a list of attributes to a friendship
     * @param attributes the atributes of the returned entity
     * @return Friendship - the converted friendship
     */
    @Override
    public Friendship extractEntity(List<String> attributes) {
        return new Friendship(attributes.get(0), attributes.get(1), LocalDateTime.parse(attributes.get(2), DATATIME_FORMATTER));
    }

    /**
     * Converts a user to the storable form
     * @param friendship E - the entity to be converted to string
     * @return String - the conversion of the user into String
     */
    @Override
    protected String createEntityAsString(Friendship friendship) {
        List<String> usersList = new ArrayList<>(friendship.getId());
        return usersList.get(0) + ";" + usersList.get(1) + ";" + friendship.getFriendsFrom().format(DATATIME_FORMATTER) + "\n";
    }
}
