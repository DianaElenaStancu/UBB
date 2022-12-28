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

public class HomeController extends AbstractController{

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
    Button removeButton, addButton, accountSettingsButton, logOutButton, chatButton;

    @FXML
    TextField searchUserTextField;


    public void setService(NetworkService networkService) {
        this.networkService = networkService;
        usersModel.setAll(getFriendships(ACCEPTED));
    }

    public void setUser(User user) {
        this.currentUser = user;
    }

    public void setPairedUser(User user){}


    @FXML
    public void initialize() {
        usernameTableColumn.setCellValueFactory(new PropertyValueFactory<>(ID));
        firstNameTableColumn.setCellValueFactory(new PropertyValueFactory<>(FIRST_NAME));
        lastNameTableColumn.setCellValueFactory(new PropertyValueFactory<>(LAST_NAME));
        emailTableColumn.setCellValueFactory(new PropertyValueFactory<>(EMAIL));
        dateTableColumn.setCellValueFactory(new PropertyValueFactory<>(FRIENDS_FROM));
        statusTableColumn.setCellValueFactory(new PropertyValueFactory<>(STATUS));


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
            chatButton.setDisable(true);
        } else {
            usersModel.setAll(getFriendships(ACCEPTED));
            removeButton.setDisable(false);
            addButton.setDisable(true);
            chatButton.setDisable(false);
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
        loadPage(this.networkService, null, null, location, LOG_IN, 320, 340);
        closePage((Stage) logOutButton.getScene().getWindow());
    }

    @FXML
    protected void accountSettingsButtonClicked() throws IOException {
        URL location = getClass().getResource("/socialnetwork/account-settings.fxml");
        loadPage(this.networkService, this.currentUser, null, location, LOG_IN, 320, 400);
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
            chatButton.setDisable(true);
        } else {
            usersModel.setAll(getFriendships(ACCEPTED));
            removeButton.setDisable(false);
            addButton.setDisable(true);
            chatButton.setDisable(false);
        }
    }


    @FXML
    protected void chatButtonClicked() throws IOException{
        UserDTO userDTO = usersTableView.getSelectionModel().getSelectedItem();
        if (userDTO != null) {
            URL location = getClass().getResource("/socialnetwork/chat.fxml");
            loadPage(this.networkService, this.currentUser, this.networkService.findUser(userDTO.getId()), location, userDTO.getId(), 600, 425);
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