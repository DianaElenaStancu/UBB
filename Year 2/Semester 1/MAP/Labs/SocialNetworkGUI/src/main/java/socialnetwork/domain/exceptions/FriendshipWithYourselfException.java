package socialnetwork.domain.exceptions;


public class FriendshipWithYourselfException extends EntityMissingException{
    public FriendshipWithYourselfException() {
        super();
    }

    public FriendshipWithYourselfException(String message) {
        super(message);
    }

    public FriendshipWithYourselfException(String message, Throwable cause) {
        super(message, cause);
    }

    public FriendshipWithYourselfException(Throwable cause) {
        super(cause);
    }

    public FriendshipWithYourselfException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}