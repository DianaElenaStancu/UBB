package socialnetwork.controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.domain.UserDTO;
import socialnetwork.domain.exceptions.EntityMissingException;
import socialnetwork.domain.exceptions.FriendshipWithYourselfException;
import socialnetwork.service.NetworkService;

import java.io.IOException;
import java.net.URL;
import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static socialnetwork.constants.Strings.*;
import static socialnetwork.gui_utils.GUIUtils.*;

public class HomeController implements Controller{

    ObservableList<UserDTO> usersModel = FXCollections.observableArrayList();
    private NetworkService networkService;
    private User currentUser;

    @FXML
    TableColumn<UserDTO, String> usernameTableColumn, firstNameTableColumn, lastNameTableColumn, emailTableColumn, statusTableColumn;
    @FXML
    TableColumn<UserDTO, LocalDateTime> dateTableColumn;

    @FXML
    TableView<UserDTO> usersTableView;

    @FXML
    CheckBox requestsCheckBox, allUsersCheckBox;

    @FXML
    Button removeButton, addButton, accountSettingsButton, logOutButton;

    @FXML
    TextField searchUserTextField;


    public void setService(NetworkService networkService) {
        this.networkService = networkService;
        usersModel.setAll(getFriendships(ACCEPTED));
    }

    public void setUser(User user) {
        this.currentUser = user;
    }

    @FXML
    public void initialize() {
        usernameTableColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        firstNameTableColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastNameTableColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        emailTableColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        dateTableColumn.setCellValueFactory(new PropertyValueFactory<>("friendsFrom"));
        statusTableColumn.setCellValueFactory(new PropertyValueFactory<>("status"));


        usersTableView.setItems(usersModel);
        addButton.setDisable(true);

        searchUserTextField.textProperty().addListener(o -> handleFilter());
    }

    private void handleFilter() {
        Predicate<UserDTO> predicate = x -> x.getId().startsWith(searchUserTextField.getText());

        if (requestsCheckBox.isSelected()) {
            usersModel.setAll(getFriendships(PENDING)
                    .stream()
                    .filter(predicate)
                    .collect(Collectors.toList()));
        } else if (allUsersCheckBox.isSelected()) {
            usersModel.setAll(getAllUsers()
                    .stream()
                    .filter(predicate)
                    .collect(Collectors.toList()));
        } else {
            usersModel.setAll(getFriendships(ACCEPTED)
                    .stream()
                    .filter(predicate)
                    .collect(Collectors.toList()));
        }

    }


    @FXML
    protected void requestsCheckBoxClicked() {
        if (requestsCheckBox.isSelected()) {
            usersModel.setAll(getFriendships(PENDING));
            allUsersCheckBox.setSelected(false);
            addButton.setDisable(false);
            removeButton.setDisable(false);
        } else {
            usersModel.setAll(getFriendships(ACCEPTED));
            removeButton.setDisable(false);
            addButton.setDisable(true);
        }
    }

    private void update() {
        if (requestsCheckBox.isSelected()) {
            usersModel.setAll(getFriendships(PENDING));
        } else if (allUsersCheckBox.isSelected()){
            usersModel.setAll(getAllUsers());
        } else {
            usersModel.setAll(getFriendships(ACCEPTED));
        }
    }

    @FXML
    protected void logOutButtonClicked() throws IOException {
        URL location = getClass().getResource("/socialnetwork/log-in.fxml");
        String title = "Login";
        loadPage(this.networkService, null, location, title, 320, 340);
        closePage((Stage) logOutButton.getScene().getWindow());
    }

    @FXML
    protected void accountSettingsButtonClicked() throws IOException {
        URL location = getClass().getResource("/socialnetwork/account-settings.fxml");
        String title = "Login";
        loadPage(this.networkService, this.currentUser, location, title, 320, 400);
        closePage((Stage) accountSettingsButton.getScene().getWindow());
    }
    @FXML
    protected void addButtonClicked() {
        UserDTO userDTO = usersTableView.getSelectionModel().getSelectedItem();
        if (userDTO != null) {
            try {
                Friendship friendship = this.networkService.findFriendship(this.currentUser.getId(), userDTO.getId());
                if(Objects.equals(friendship.getStatus(), PENDING) && Objects.equals(friendship.getUser2(), this.currentUser.getId())) {
                    this.networkService.updateFriendship(this.currentUser.getId(), userDTO.getId(), LocalDateTime.now(), ACCEPTED);
                    showInformationAlert(SUCCESS, OPERATION_FINISHED_SUCCESSFULLY, EMPTY);
                } else if (Objects.equals(friendship.getStatus(), ACCEPTED) ) {
                    showInformationAlert(FRIENDSHIP_INFO, OPERATION_FAILED, ALREADY_FRIENDS);
                }
                else {
                    showInformationAlert(REQUEST_INFO, OPERATION_FINISHED_SUCCESSFULLY, YOU_HAVE_TO_WAIT_FOR_USER_TO_ACCEPT_REQUEST(userDTO));
                }
            } catch(FriendshipWithYourselfException friendshipWithYourselfException) {
                showInformationAlert(REQUEST_INFO, OPERATION_FAILED, CANT_BE_FRIEND_WITH_YOURSELF);
            }
            catch (EntityMissingException entityMissingException){
                this.networkService.addFriendship(this.currentUser.getId(), userDTO.getId(), PENDING);
                showInformationAlert(REQUEST_INFO, OPERATION_FINISHED_SUCCESSFULLY, YOU_HAVE_TO_WAIT_FOR_USER_TO_ACCEPT_REQUEST(userDTO));

            } catch (Exception exception) {
                showInformationAlert(REQUEST_INFO, OPERATION_FAILED, exception.getMessage());
            }
        }
        update();

    }

    @FXML
    protected void removeButtonClicked() {
        UserDTO userDTO = usersTableView.getSelectionModel().getSelectedItem();
        if (userDTO != null) {
            try {
                this.networkService.removeFriendship(this.currentUser.getId(), userDTO.getId());
                showInformationAlert(REMOVE_INFO, OPERATION_FINISHED_SUCCESSFULLY, EMPTY);

            } catch (Exception exception) {
                showInformationAlert(REMOVE_INFO, OPERATION_FAILED, exception.getMessage());
            }
        }
        update();
    }

    @FXML
    protected void allUsersCheckBoxClicked() {
        if (allUsersCheckBox.isSelected()) {
            usersModel.setAll(getAllUsers());
            requestsCheckBox.setSelected(false);
            removeButton.setDisable(true);
            addButton.setDisable(false);
        } else {
            usersModel.setAll(getFriendships(ACCEPTED));
            removeButton.setDisable(false);
            addButton.setDisable(true);
        }
    }
    private List<UserDTO> getFriendships(String status) {
        Iterable<User> friendsIterable = this.networkService.showUserFriends(currentUser.getId());
        List<User> friendsList =
                StreamSupport.stream(friendsIterable.spliterator(), false).toList();

        return friendsList.stream().map(x -> this.networkService.findUser(x.getId())).toList()
                .stream()
                .filter(x -> Objects.equals(this.networkService.findFriendship(x.getId(), currentUser.getId()).getStatus(), status))
                .map(x -> new UserDTO(x.getId(),x.getFirstName(), x.getLastName(), x.getEmail(),
                        this.networkService.findFriendship(x.getId(), currentUser.getId()).getFriendsFrom(), this.networkService.getStatusOfFriendship(this.currentUser.getId(), x.getId())))
                .sorted(Comparator.comparing(UserDTO::getId))
                .collect(Collectors.toList());
    }

    private List<UserDTO> getAllUsers() {
        Iterable<User> usersIterable = this.networkService.getAllUsers();
        List<User> usersList =
                StreamSupport.stream(usersIterable.spliterator(), false).toList();

        return usersList.stream().map(x -> this.networkService.findUser(x.getId())).toList()
                .stream()
                .map(x -> new UserDTO(x.getId(),x.getFirstName(), x.getLastName(), x.getEmail(),
                        LocalDateTime.now(), this.networkService.getStatusOfFriendship(x.getId(), this.currentUser.getId())))
                .sorted(Comparator.comparing(UserDTO::getId))
                .collect(Collectors.toList());

    }
}