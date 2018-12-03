package ru.itmo.webmail.model.service;

import com.google.common.base.CharMatcher;
import com.google.common.hash.Hashing;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.UserRepository;
import ru.itmo.webmail.model.repository.impl.UserRepositoryImpl;

import java.nio.charset.StandardCharsets;
import java.util.List;

@SuppressWarnings("UnstableApiUsage")
public class UserService {
    private static final String USER_PASSWORD_SALT = "dc3475f2b301851b";

    public UserRepository userRepository = new UserRepositoryImpl();

    public void validateRegistration(User user, String password) throws ValidationException {
        if (user.getEmail() == null || user.getEmail().isEmpty()) {
            throw new ValidationException("Email is required");
        }
        if (!user.getEmail().contains("@") || CharMatcher.is('@').countIn(user.getEmail()) != 1) {
            throw new ValidationException("Wrong email pattern");
        }
        if (user.getEmail().length() < 5) {
            throw new ValidationException("Email can't be shorter than 5");
        }
        if (user.getEmail().length() > 20) {
            throw new ValidationException("Email can't be longer than 20");
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
        if (userRepository.findByLoginOrEmail(user.getLogin()) != null) {
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
    }

    public void register(User user, String password) {
        userRepository.save(user, getPasswordSha(password));
    }

    public List<User> findAll() {
        return userRepository.findAll();
    }

    public void validateEnter(String loginOrEmail, String password) throws ValidationException {
        if (loginOrEmail == null || loginOrEmail.isEmpty()) {
            throw new ValidationException("Login or email is required");
        }
        if (password == null || password.isEmpty()) {
            throw new ValidationException("Password is required");
        }

        User user = userRepository.findByLoginOrEmailAndPasswordSha(loginOrEmail, getPasswordSha(password));
        if (user == null) {
            throw new ValidationException("Invalid login or password");
        }

        if (!user.isConfirmed()) {
            throw new ValidationException("Verify email first");
        }
    }

    private String getPasswordSha(String password) {
        return Hashing.sha256().hashString(USER_PASSWORD_SALT + password,
                StandardCharsets.UTF_8).toString();
    }

    public User authorize(String loginOrEmail, String password) {
        return userRepository.findByLoginOrEmailAndPasswordSha(loginOrEmail, getPasswordSha(password));
    }

    public User findByLoginOrEmail(String login) {
        return userRepository.findByLoginOrEmail(login);
    }

    public User findById(Long id) {
        return userRepository.findById(id);
    }
}
