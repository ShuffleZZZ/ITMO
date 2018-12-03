package ru.itmo.webmail.model.domain;

import java.io.Serializable;

public class User implements Serializable {
    private String login;
    private String passwordSha1;
    private String email;
    private long id;


    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public long getID() {
        return id;
    }

    public void setID(long id) { this.id = id; }

    public String getEmail() { return email; }

    public void setEmail(String email) { this.email = email; }

    public String getPasswordSha1() {
        return passwordSha1;
    }

    public void setPasswordSha1(String passwordSha1) {
        this.passwordSha1 = passwordSha1;
    }
}