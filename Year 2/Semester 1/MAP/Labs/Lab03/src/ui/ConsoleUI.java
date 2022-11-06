package ui;

import domain.User;
import domain.exceptions.EntityAlreadyExistsException;
import domain.exceptions.EntityMissingException;
import domain.validators.ValidationException;
import service.UserService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ConsoleUI implements UI {
    String username;
    private final UserService userService;

    public ConsoleUI(UserService userService) {
        this.userService = userService;
        username = null;
    }


    private static class ConsoleLogged implements UI {
        private final User currentUser;
        private final UserService userService;
        private final BufferedReader bufferedReader;

        public ConsoleLogged(User currentUser, UserService userService) {
            this.currentUser = currentUser;
            this.userService = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("1 - Add friend");
            System.out.println("2 - Remove friend");
            System.out.println("3 - Delete account");
            System.out.println("4 - Exit");
        }

        private void addFriend() {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }
            this.userService.addFriendship(currentUser.getId(), username);
        }

        private void removeFriend() {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }
            this.userService.removeFriendShip(currentUser.getId(), username);
        }

        private void deleteAccount() {
            this.userService.removeUser(currentUser.getId());
        }

        @Override
        public void run() {
            while (true) {
                printMenu();
                String command;
                try {
                    command = bufferedReader.readLine();
                } catch (IOException exception) {
                    System.out.println("Error reading the command");
                    continue;
                }
                try {
                    switch (command) {
                        case "1":
                            addFriend();
                            break;
                        case "2":
                            removeFriend();
                            break;
                        case "3":
                            deleteAccount();
                        case "4":
                            return;
                    }
                } catch (EntityMissingException | EntityAlreadyExistsException EntityException) {
                    System.out.println(EntityException.getMessage());
                }
            }

        }
    }

    private static class ConsoleUnlogged implements UI {
        private final UserService userService;
        private final BufferedReader bufferedReader;

        public ConsoleUnlogged(UserService userService) {
            this.userService = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("1 - Add user");
            System.out.println("2 - Number of communities");
            System.out.println("3 - Most social community");
            System.out.println("4 - Log in");
            System.out.println("5 - Exit");
        }

        private void addUser() {
            String username;
            String password;
            String email;
            String firstName;
            String lastName;
            try {
                System.out.print("Username: ");
                username = bufferedReader.readLine();
                System.out.print("Password: ");
                password = bufferedReader.readLine();
                System.out.print("Email: ");
                email = bufferedReader.readLine();
                System.out.print("First name: ");
                firstName = bufferedReader.readLine();
                System.out.print("Last name: ");
                lastName = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the data");
                return;
            }
            userService.addUser(username, password, email, firstName, lastName);
        }

        private void numberOfCommunities() {
            System.out.println("Number of communities is equal with " + userService.numberOfCommunities());
        }

        private void mostSocialCommunity() {
            System.out.println(userService.mostSocialCommunity());
        }

        private void logIn() {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }

            User user;
            try {
                user = userService.findUser(username);
            } catch (EntityMissingException inexistentEntityException) {
                System.out.println(inexistentEntityException.getMessage());
                return;
            }
            ConsoleLogged consoleLogged = new ConsoleLogged(user, this.userService);
            consoleLogged.run();
        }

        @Override
        public void run() {
            while (true) {
                printMenu();
                String command;
                try {
                    command = bufferedReader.readLine();
                } catch (IOException exception) {
                    System.out.println("Error reading the command");
                    continue;
                }
                try {
                    switch (command) {
                        case "1":
                            addUser();
                            break;
                        case "2":
                            numberOfCommunities();
                            break;
                        case "3":
                            mostSocialCommunity();
                            break;
                        case "4":
                            logIn();
                            break;
                        case "5":
                            return;
                        default:
                            System.out.println("Unknown command!");
                    }
                } catch (EntityAlreadyExistsException | ValidationException EntityException) {
                    System.out.println(EntityException.getMessage());
                }
            }
        }
    }

    @Override
    public void run() {
        ConsoleUnlogged consoleUnlogged = new ConsoleUnlogged(this.userService);
        consoleUnlogged.run();
    }
}
