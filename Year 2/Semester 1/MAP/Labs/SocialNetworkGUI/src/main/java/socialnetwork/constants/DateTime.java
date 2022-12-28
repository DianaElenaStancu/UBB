package socialnetwork.constants;

import java.time.format.DateTimeFormatter;

public class DateTime {
    public static final DateTimeFormatter DATATIME_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
    public static final DateTimeFormatter DATATIME_FORMATTER_NO_YEAR = DateTimeFormatter.ofPattern("MM-dd HH:mm");

}
