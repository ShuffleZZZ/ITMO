package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.User;

import java.util.List;

public interface UserRepository {
    void save(User user);
    User findByLogin(String login);
    User findByEmail(String email);
    List<User> findAll();
    int findCount();
    User find(long Id);
}
