package socialnetwork.domain.exceptions;

public class EntityMissingException extends RuntimeException{
    public EntityMissingException() {
    }

    public EntityMissingException(String message) {
        super(message);
    }

    public EntityMissingException(String message, Throwable cause) {
        super(message, cause);
    }

    public EntityMissingException(Throwable cause) {
        super(cause);
    }

    public EntityMissingException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
