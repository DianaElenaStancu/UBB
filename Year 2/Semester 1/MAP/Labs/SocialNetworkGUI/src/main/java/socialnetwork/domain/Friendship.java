package socialnetwork.domain;

import java.time.LocalDateTime;
import java.util.*;

public class Friendship extends Entity<Set<String>>{
    private static final UUID serialVersionUID = UUID.randomUUID();
    private LocalDateTime friendsFrom;

    private String status;

    public Friendship(String user1, String user2, LocalDateTime friendshipDate, String status) {
        super(new LinkedHashSet<>(Arrays.asList(user1, user2)));
        this.friendsFrom = friendshipDate;
        this.status = status;
    }

    public Friendship(String user1, String user2, LocalDateTime friendshipDate) {
        super(new LinkedHashSet<>(Arrays.asList(user1, user2)));
        this.friendsFrom = LocalDateTime.now();
        this.status = "accepted";
    }

    public Friendship(String user1, String user2, String status) {
        super(new LinkedHashSet<>(Arrays.asList(user1, user2)));
        this.friendsFrom = LocalDateTime.now();
        this.status = status;
    }

    public Friendship(String user1, String user2) {
        super(new LinkedHashSet<>(Arrays.asList(user1, user2)));
        this.friendsFrom = LocalDateTime.now();
        this.status = "accepted";
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }

    public void setFriendsFrom(LocalDateTime friendsFrom) {
        this.friendsFrom = friendsFrom;
    }

    public String getUser1() {
        return new ArrayList<>(this.getId()).get(0);
    }
    public String getUser2() {
        return new ArrayList<>(this.getId()).get(1);
    }

    @Override
    public String toString() {
        List<String> usersList = new ArrayList<>(this.getId());
        return  usersList.get(0) + " and " + usersList.get(1) + " since " + friendsFrom;
    }
}
