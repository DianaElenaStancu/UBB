package socialnetwork.ui;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.exceptions.EntityAlreadyExistsException;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.service.NetworkService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.time.DateTimeException;
import java.time.LocalDateTime;
import java.time.format.DateTimeParseException;

import static socialnetwork.constants.DateTime.DATATIME_FORMATTER;

public class ConsoleUI implements UI {
    String username;
    private final NetworkService networkService;

    public ConsoleUI(NetworkService userService) {
        this.networkService = userService;
        username = null;
    }


    private static class ConsoleLogged implements UI {
        private final User currentUser;
        private final NetworkService service;
        private final BufferedReader bufferedReader;

        public ConsoleLogged(User currentUser, NetworkService userService) {
            this.currentUser = currentUser;
            this.service = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("\u001B[33m1 - Add friend");
            System.out.println("2 - Remove friend");
            System.out.println("3 - Update account");
            System.out.println("4 - Delete account");
            System.out.println("5 - Show my friends");
            System.out.println("6 - Update friendship");
            System.out.println("7 - Exit");
        }

        private void addFriend() {
            String username;

            System.out.print("\u001B[34mUsername: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("\u001B[31mError reading the username");
                return;
            }
            try {
                this.service.addFriendship(currentUser.getId(), username);
                System.out.println("\u001B[32mSucces");
            } catch (Exception e) {
                System.out.println("\u001B[31m" + e.getMessage());
            }

        }

        private void removeFriend() {
            String username;

            System.out.print("\u001B[34mUsername: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("\u001B[31mError reading the username");
                return;
            }
            try {
                this.service.removeFriendship(currentUser.getId(), username);
                System.out.println("\u001B[32mSucces");
            } catch (Exception e) {
                System.out.println("\u001B[31m" + e.getMessage());
            }
        }

        private void updateAccount() {
            String password;
            String email;
            String firstName;
            String lastName;
            try {
                System.out.print("\u001B[34mFirst name: ");
                firstName = bufferedReader.readLine();
                System.out.print("Last name: ");
                lastName = bufferedReader.readLine();
                System.out.print("Email: ");
                email = bufferedReader.readLine();
                System.out.print("Password: ");
                password = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("\u001B[31mError reading the data");
                return;
            }
            try {
                this.service.updateUser(currentUser.getId(), firstName, lastName, email, password);
                System.out.println("\u001B[32mSucces");
            } catch (Exception e) {
                System.out.println("\u001B[31m" + e.getMessage());
            }
        }

        private void deleteAccount() {
            try{
                this.service.removeUser(currentUser.getId());
                System.out.println("\u001B[32mSucces");
            } catch (Exception e) {
                System.out.println("\u001B[31m" + e.getMessage());
            }
        }

        private void showMyFriends() {
            Iterable<User> friends= service.showUserFriends(currentUser);
            System.out.println("\u001B[32m");
            for(User user : friends) {
                System.out.println(user);
            }
            System.out.println();
        }

        private void updateFriendship() {
            String username;
            String localDateTimeString;
            LocalDateTime localDateTime;

            try {
                System.out.print("\u001B[34mFriend's username: ");
                username = bufferedReader.readLine();

                System.out.print("\u001B[34mDate: ");
                localDateTimeString = bufferedReader.readLine();
                localDateTime = LocalDateTime.parse(localDateTimeString, DATATIME_FORMATTER);

            } catch (IOException exception) {
                System.out.println("\u001B[31mError reading the data");
                return;
            } catch (DateTimeParseException exception) {
                System.out.println("\u001B[31mError parsing the date");
                return;
            }
            try {
                this.service.updateFriendship(currentUser.getId(), username, localDateTime);
                System.out.println("\u001B[32mSucces");
            } catch (Exception e) {
                System.out.println("\u001B[31m" + e.getMessage());
            }
        }
        @Override
        public void run() {
            while (true) {
                printMenu();
                String command;
                try {
                    command = bufferedReader.readLine();
                } catch (IOException exception) {
                    System.out.println("\u001B[31mError reading the command");
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
                            updateAccount();
                            break;
                        case "4":
                            deleteAccount();
                        case "5":
                            showMyFriends();
                            break;
                        case "6":
                            updateFriendship();
                            break;
                        case "7":
                            return;
                        default:
                            System.out.println("\u001B[31mUnknown command!");
                    }
                } catch (EntityMissingException | EntityAlreadyExistsException EntityException) {
                    System.out.println("\u001B[31m" + EntityException.getMessage());
                }
            }

        }
    }

    private static class ConsoleUnlogged implements UI {
        private final NetworkService userService;
        private final BufferedReader bufferedReader;

        public ConsoleUnlogged(NetworkService userService) {
            this.userService = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("\u001B[33m1 - Show Users");
            System.out.println("2 - Show friendships");
            System.out.println("3 - Add user");
            System.out.println("4 - Number of communities");
            System.out.println("5 - Most social community");
            System.out.println("6 - Log in");
            System.out.println("7 - Clear social network");
            System.out.println("8 - Exit");
        }

        private void showUsers() {
            System.out.println("\u001B[32m");
            Iterable<User> allUsers = this.userService.getAllUsers();
            for(User user : allUsers) {
                System.out.println(user);
            }
            System.out.println();
        }

        private void showFriendships() {
            System.out.println("\u001B[32m");
            Iterable<Friendship> allFriendships = this.userService.getAllFriendships();
            for(Friendship friendship : allFriendships) {
                System.out.println(friendship);
            }
            System.out.println();
        }

        private void addUser() {
            String username;
            String password;
            String email;
            String firstName;
            String lastName;
            try {
                System.out.print("\u001B[34mUsername: ");
                username = bufferedReader.readLine();
                System.out.print("First name: ");
                firstName = bufferedReader.readLine();
                System.out.print("Last name: ");
                lastName = bufferedReader.readLine();
                System.out.print("Email: ");
                email = bufferedReader.readLine();
                System.out.print("Password: ");
                password = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("\u001B[31mError reading the data");
                return;
            }
            try {
                userService.addUser(username, firstName, lastName, email, password);
                System.out.println("\u001B[32mSucces");
            } catch (Exception e) {
                System.out.println("\u001B[31m" + e.getMessage());
            }
        }

        private void numberOfCommunities() {
            System.out.println("\u001B[32mNumber of communities is equal with " + userService.numberOfCommunities());
        }

        private void mostSocialCommunity() {
            System.out.println("\u001B[32m" + userService.mostSocialCommunity());
        }

        private void logIn() {
            String username;

            System.out.print("\u001B[34mUsername: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("\u001B[31mError reading the username");
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

        public void clear() {
            this.userService.clear();
            System.out.println("\u001B[32mSucces");
        }

        @Override
        public void run() {
            while (true) {
                printMenu();
                String command;
                try {
                    command = bufferedReader.readLine();
                } catch (IOException exception) {
                    System.out.println("\u001B[31mError reading the command");
                    continue;
                }
                try {
                    switch (command) {
                        case "1":
                            showUsers();
                            break;
                        case "2":
                            showFriendships();
                            break;
                        case "3":
                            addUser();
                            break;
                        case "4":
                            numberOfCommunities();
                            break;
                        case "5":
                            mostSocialCommunity();
                            break;
                        case "6":
                            logIn();
                            break;
                        case "7":
                            clear();
                            break;
                        case "8":
                            return;
                        default:
                            System.out.println("\u001B[31mUnknown command!");
                    }
                } catch (EntityAlreadyExistsException | ValidationException EntityException) {
                    System.out.println("\u001B[31m"+EntityException.getMessage());
                }
            }
        }
    }

    @Override
    public void run() {
        ConsoleUnlogged consoleUnlogged = new ConsoleUnlogged(this.networkService);
        consoleUnlogged.run();
    }
}
