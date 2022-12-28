package socialnetwork.domain;

import java.time.LocalDateTime;

import static socialnetwork.constants.DateTime.DATATIME_FORMATTER_NO_YEAR;

public class Message extends Entity<String>{
    private String receiver;
    private String sender;
    private String text;
    private LocalDateTime date;

    public Message(String id, String text, LocalDateTime date, String sender, String receiver) {
        super(id);
        this.text = text;
        this.date = date;
        this.sender = sender;
        this.receiver = receiver;
    }

    public Message(String text, LocalDateTime date, String sender, String receiver) {
        this.text = text;
        this.date = date;
        this.sender = sender;
        this.receiver = receiver;
    }

    public String getReceiver() {
        return receiver;
    }

    public void setReceiver(String receiver) {
        this.receiver = receiver;
    }

    public String getSender() {
        return sender;
    }

    public void setSender(String sender) {
        this.sender = sender;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return sender +
                ": " + text + "       " +
                '(' + date.format(DATATIME_FORMATTER_NO_YEAR) + ')';
    }
}
