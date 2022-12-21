package socialnetwork.domain.validators;

import socialnetwork.domain.Friendship;

import java.time.LocalDateTime;

public class FriendshipValidator implements Validator<Friendship> {
    /**
     * Validates a friendship
     * @param friendship Friendship - the friendship to be validated
     * @throws ValidationException with the errors if the friendship is not valid
     */
    public void validate(Friendship friendship) {
        String errorMessage = "";
        if(friendship.getId().size() == 1) {
            errorMessage += friendship.getUser1() + " cannot be friend to itself!\n";
        }
        if(friendship.getFriendsFrom().isAfter(LocalDateTime.now().plusSeconds(5))) {
            errorMessage += "Friendship date cannot be in the future!";
        }
        if(errorMessage.length() > 0) {
            throw new ValidationException(errorMessage);
        }
    }
}
