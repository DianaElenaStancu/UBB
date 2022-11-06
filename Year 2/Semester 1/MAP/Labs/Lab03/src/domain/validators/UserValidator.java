package domain.validators;

import domain.User;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class UserValidator implements Validator<User> {
    /**
     * Verifies if a string is a valid id
     * @param username - the string that has to be validated
     * @return errorMessages - String that contains the validation errors
     */
    private String validateId(String username) {
        String errorMessages = "";
        if (username.length() <= 2)
            errorMessages += "Username is too short.";
        return errorMessages;
    }

    /**
     * Verifies if a string is a valid password
     * @param password - the string that has to be validated
     * @return errorMessages - String that contains the validation errors
     */
    private String validatePassword(String password) {
        String errorMessages = "";
        if (password.length() <= 2)
            errorMessages += "Password is too short.";
        return errorMessages;
    }

    /**
     * Verifies if a string is a valid name
     * @param name - the string that has to be validated
     * @return errorMessages - String that contains the validation errors
     */
    private String validateName(String name) {
        String errorMessages = "";
        if (name.length() <= 2)
            errorMessages += "Name is too short." + "\n";

        Pattern pattern = Pattern.compile("^[A-Za-z\\s]*$");
        Matcher matcher = pattern.matcher(name);
        if (matcher.matches())
            errorMessages += "Name must contain only letters and spaces.";
        return errorMessages;
    }

    /**
     * Verifies if a string is a valid email
     * @param email - the string that has to be validated
     * @return errorMessages - String that contains the validation errors
     */
    private String validateEmail(String email) {
        String errorMessages = "";
        Pattern pattern = Pattern.compile("^(.+)@(.+)$");
        Matcher matcher = pattern.matcher(email);
        if (matcher.matches())
            errorMessages += "Invalid email.";
        return errorMessages;
    }

    /**
     * Validates an user
     * @param user - User
     * @throws ValidationException only if a user field is not valid; contains the validation errors
     */
    @Override
    public void validate(User user) throws ValidationException {
        String errorMessages = "";

        String usernameErrors = this.validateId(user.getId());
        if (!usernameErrors.isEmpty())
            errorMessages += usernameErrors + "\n";

        String passwordErrors = this.validatePassword(user.getId());
        if (!passwordErrors.isEmpty())
            errorMessages += passwordErrors + "\n";

        String firstNameErrors = this.validateName(user.getFirstName());
        if (!firstNameErrors.isEmpty())
            errorMessages += firstNameErrors + "\n";

        String lastNameErrors = this.validateName(user.getLastName());
        if (!lastNameErrors.isEmpty())
            errorMessages += lastNameErrors + "\n";

        String emailErrors = this.validateEmail(user.getEmail());
        if (!emailErrors.isEmpty())
            errorMessages += emailErrors;

        if (!errorMessages.isEmpty())
            throw new ValidationException(errorMessages);
    }
}
