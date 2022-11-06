package repository.file;

import domain.User;
import repository.memory.InMemoryNetworkRepository;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;

public class NetworkFileRepository extends InMemoryNetworkRepository {
    String usersFilename;
    String friendshipsFilename;

    public NetworkFileRepository(String usersFilename, String friendshipsFilename) {
        this.usersFilename = usersFilename;
        this.friendshipsFilename = friendshipsFilename;
        loadData();
    }

    private void loadData() {
        try(BufferedReader bufferedReader = new BufferedReader(new FileReader(this.usersFilename))) {
            String line;
            while((line = bufferedReader.readLine()) != null) {
                List<String> users = Arrays.asList(line.split(";"));
                this.addUser(new User(users.get(0), users.get(1), users.get(2), users.get(3), users.get(4)));
            }
        }
        catch (IOException ioException) {
            ioException.printStackTrace();
        }
        try(BufferedReader bufferedReader = new BufferedReader(new FileReader(this.friendshipsFilename))) {
            String line;
            while((line = bufferedReader.readLine()) != null) {
                List<String> users = Arrays.asList(line.split(";"));
                this.createFriendship(new User(users.get(0), "", "", "", ""),
                        new User(users.get(1), "", "", "", ""));
            }
        }
        catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }
}
