package socialnetwork.controllers;

import socialnetwork.domain.User;
import socialnetwork.service.NetworkService;

public interface Controller {
    void setService(NetworkService networkService);

    void setUser(User user);

    void setPairedUser(User user);
}
