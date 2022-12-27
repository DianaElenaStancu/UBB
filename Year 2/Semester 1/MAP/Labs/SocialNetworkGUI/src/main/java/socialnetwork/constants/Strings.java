package socialnetwork.constants;

import socialnetwork.domain.UserDTO;

public class Strings {
    public static final String  FRIENDSHIP_INFO = "Friendship info";
    public static final String REQUEST_INFO = "Request info";
    public static final String REMOVE_INFO = "Remove info";
    public static final String SIGN_UP_INFO = "Sign up info";
    public static final String RESET_INFO = "Reset info";
    public static final String LOG_IN_INFO = "Sign in info";
    public static final String ALREADY_FRIENDS = "You are already friends";
    public static final String CANT_BE_FRIEND_WITH_YOURSELF = "You can't be friend with yourself!";
    public static final String ADD_THE_SAME_PASSWORD = "Please add the same password!";
    public static final String EMPTY = "";
    public static final String SUCCESS = "Success";
    public static final String OPERATION_FINISHED_SUCCESSFULLY = "Operation finished successfully!";
    public static final String OPERATION_FAILED = "Operation failed!";
    public static final String REGISTER = "Register";
    public static final String LOG_IN = "Log in";
    public static final String LOG_IN_FAILED = "Sign up failed";
    public static final String WRONG_PASSWORD_OR_USERNAME = "Wrong password or username";
    public static final String INVALID_CREDENTIALS = "Invalid Credentials";
    public static final String ACCEPTED = "accepted";
    public static final String PENDING = "pending";
    public static String YOU_HAVE_TO_WAIT_FOR_USER_TO_ACCEPT_REQUEST(UserDTO user) {
        return "You have to wait for " + user.getId() + " to accept your request";
    }

    public static final String ID = "id";
    public static final String FIRST_NAME = "firstName";
    public static final String LAST_NAME = "lastName";
    public static final String EMAIL = "email";
    public static final String FRIENDS_FROM = "friendsFrom";
    public static final String STATUS = "status";
    public static final String CHAT = "chat";

}
