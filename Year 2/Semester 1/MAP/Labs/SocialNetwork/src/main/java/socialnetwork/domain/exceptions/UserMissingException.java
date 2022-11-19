package socialnetwork.domain.exceptions;

public class UserMissingException extends EntityMissingException{
    public UserMissingException() {
        super();
    }

    public UserMissingException(String message) {
        super(message);
    }

    public UserMissingException(String message, Throwable cause) {
        super(message, cause);
    }

    public UserMissingException(Throwable cause) {
        super(cause);
    }

    public UserMissingException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
