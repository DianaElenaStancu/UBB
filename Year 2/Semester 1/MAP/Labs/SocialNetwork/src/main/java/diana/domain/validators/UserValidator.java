package diana.domain.validators;

import diana.domain.User;

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
        Pattern pattern = Pattern.compile("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{4,}$");
        Matcher matcher = pattern.matcher(password);
        if (!matcher.matches())
            errorMessages += "Invalid password. You need at least 1 upper case, 1 lower case, 1 digit, 1 special character.";
        return errorMessages;
    }

    /**
     * Verifies if a string is a valid name
     * @param name - the string that has to be validated
     * @return errorMessages - String that contains the validation errors
     */
    public String validateName(String name) {
        String errorMessages = "";
        Pattern pattern = Pattern.compile("^[A-Za-z\\s]{3,}$");
        Matcher matcher = pattern.matcher(name);
        if (!matcher.matches())
            errorMessages += "Name must contain only letters and spaces. Minimum length 3.";
        return errorMessages;
    }

    /**
     * Verifies if a string is a valid email
     * @param email - the string that has to be validated
     * @return errorMessages - String that contains the validation errors
     */
    private String validateEmail(String email) {
        String errorMessages = "";
        Pattern pattern = Pattern.compile("^(.{3,})@(.{3,})$");
        Matcher matcher = pattern.matcher(email);
        if (!matcher.matches())
            errorMessages += "Invalid email. Minimum length 3.";
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
