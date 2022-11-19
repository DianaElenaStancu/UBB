package socialnetwork.domain.exceptions;

public class FriendshipAlreadyExistsException extends EntityAlreadyExistsException{
    public FriendshipAlreadyExistsException() {
        super();
    }

    public FriendshipAlreadyExistsException(String message) {
        super(message);
    }

    public FriendshipAlreadyExistsException(String message, Throwable cause) {
        super(message, cause);
    }

    public FriendshipAlreadyExistsException(Throwable cause) {
        super(cause);
    }

    public FriendshipAlreadyExistsException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
