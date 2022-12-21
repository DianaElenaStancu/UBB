package socialnetwork.config;

import java.io.IOException;
import java.util.Properties;

public class Config {
    public static Properties getProperties() {
        Properties properties=new Properties();
        try {
            properties.load(Config.class.getClassLoader()
                    .getResourceAsStream("config.properties"));
            return properties;
        } catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException("Cannot load config properties");
        }
    }
}
