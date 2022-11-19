package socialnetwork.domain.exceptions;

public class FriendshipMissingException extends EntityMissingException{
    public FriendshipMissingException() {
        super();
    }

    public FriendshipMissingException(String message) {
        super(message);
    }

    public FriendshipMissingException(String message, Throwable cause) {
        super(message, cause);
    }

    public FriendshipMissingException(Throwable cause) {
        super(cause);
    }

    public FriendshipMissingException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
