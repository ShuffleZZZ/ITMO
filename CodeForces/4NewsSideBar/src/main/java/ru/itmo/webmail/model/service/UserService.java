package ru.itmo.webmail.model.service;

import com.google.common.base.CharMatcher;
import com.google.common.hash.Hashing;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.UserRepository;
import ru.itmo.webmail.model.repository.impl.UserRepositoryImpl;

import java.nio.charset.StandardCharsets;
import java.util.List;

public class UserService {
    private static final String USER_PASSWORD_SALT = "dc3475f2b301851b";

    private UserRepository userRepository = new UserRepositoryImpl();

    public void validateRegistration(User user, String password, String confirmation) throws ValidationException {
        if (user.getEmail() == null || user.getEmail().isEmpty()) {
            throw new ValidationException("Email is required");
        }
        if (!user.getEmail().contains("@") || CharMatcher.is('@').countIn(user.getEmail()) != 1) {
            throw new ValidationException("Wrong email pattern");
        }
        if (user.getEmail().length() < 5) {
            throw new ValidationException("Email can't be shorter than 5");
        }
        if (userRepository.findByEmail(user.getEmail()) != null) {
            throw new ValidationException("Email is already in use");
        }
        if (user.getLogin() == null || user.getLogin().isEmpty()) {
            throw new ValidationException("Login is required");
        }
        if (!user.getLogin().matches("[a-z]+")) {
            throw new ValidationException("Login can contain only lowercase Latin letters");
        }
        if (user.getLogin().length() > 8) {
            throw new ValidationException("Login can't be longer than 8");
        }
        if (userRepository.findByLogin(user.getLogin()) != null) {
            throw new ValidationException("Login is already in use");
        }

        if (password == null || password.isEmpty()) {
            throw new ValidationException("Password is required");
        }
        if (password.length() < 4) {
            throw new ValidationException("Password can't be shorter than 4");
        }
        if (password.length() > 32) {
            throw new ValidationException("Password can't be longer than 32");
        }
        if (confirmation == null || confirmation.isEmpty()) {
            throw new ValidationException("Confirmation is required");
        }
        if (!password.equals(confirmation)) {
            throw new ValidationException("Passwords don't match");
        }
    }

    public User validateEntry(String userName, String password) throws ValidationException {
        User user = userRepository.findByLogin(userName);
        if (user == null) {
            user = userRepository.findByEmail(userName);
        }
        if (user == null) {
            throw new ValidationException("No such user");
        }
        if (!user.getPasswordSha1().equals(Hashing.sha256().hashString(USER_PASSWORD_SALT + password,
                StandardCharsets.UTF_8).toString())) {
            throw new ValidationException("Wrong password");
        }
        return user;
    }

    public void register(User user, String password) {
        user.setPasswordSha1(Hashing.sha256().hashString(USER_PASSWORD_SALT + password,
                StandardCharsets.UTF_8).toString());
        user.setID(findCount() + 1);
        userRepository.save(user);
    }

    public List<User> findAll() {
        return userRepository.findAll();
    }

    public int findCount() { return userRepository.findCount(); }

    public User find(long id) {
        return userRepository.find(id);
    }
}