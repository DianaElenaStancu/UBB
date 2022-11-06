package config;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Config {

   /* public static String CONFIG_LOCATION=Config.class.getClassLoader()
            .getResourceAsStream("config/config.properties");*/
           // .getResource("config/config.properties").getFile();
    public static Properties getProperties() {
        Properties properties=new Properties();
        try {
            //System.out.println(CONFIG_LOCATION);
            properties.load(Config.class.getClassLoader()
                    .getResourceAsStream("config/config.properties"));
            return properties;
        } catch (IOException e) {
            e.printStackTrace();
            throw new RuntimeException("Cannot load config properties");
        }
    }
}
