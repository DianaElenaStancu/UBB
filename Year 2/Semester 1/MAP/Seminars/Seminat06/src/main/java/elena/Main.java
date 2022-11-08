package elena;

import elena.domain.User;
import elena.repository.UserDbRepo;

public class Main {
    public static void main(String[] args) {
        String url ="jdbc:postgresql://localhost:5432/academic";
        UserDbRepo userDbRepo = new UserDbRepo(url, "postgres", "parola");
        User user  = new User("Apostol", "Mihai");
        userDbRepo.findAll().forEach(System.out::println);

    }
}