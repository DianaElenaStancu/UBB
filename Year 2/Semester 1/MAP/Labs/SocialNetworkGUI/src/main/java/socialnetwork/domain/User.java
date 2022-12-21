package socialnetwork.domain;

public class User extends Entity<String>{

//    private static final UUID serialVersionUUID = UUID.randomUUID();
    private String firstName;
    private String lastName;
    private String email;
    private String password;

    public User(String id, String firstName, String lastName, String email, String password) {
        super(id);
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    @Override
    public String toString() {
        return "first name='" + firstName + '\'' +
                "| last name='" + lastName + '\'' +
                "| email='" + email + '\'';
    }
}