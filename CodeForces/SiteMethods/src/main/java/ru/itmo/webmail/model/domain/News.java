package ru.itmo.webmail.model.domain;

import java.io.Serializable;

public class News implements Serializable {
    private long userId;
    private String text;

    public long getUserID() {
        return userId;
    }

    public void setUserID(long userId) { this.userId = userId; }

    public String getText() { return text; }

    public void setText(String text) { this.text = text; }
}
