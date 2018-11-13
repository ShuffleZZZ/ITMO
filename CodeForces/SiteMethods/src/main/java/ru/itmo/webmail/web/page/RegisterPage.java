package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class RegisterPage extends Page {
    private void register(HttpServletRequest request, Map<String, Object> view) {
        User user = new User();
        user.setEmail(request.getParameter("email"));
        user.setLogin(request.getParameter("login"));
        String password = request.getParameter("password");
        String confirmation = request.getParameter("passwordConfirmation");

        try {
            userService.validateRegistration(user, password, confirmation);
        } catch (ValidationException e) {
            view.put("email", user.getEmail());
            view.put("login", user.getLogin());
            view.put("password", password);
            view.put("passwordConfirmation", confirmation);
            view.put("error", e.getMessage());
            return;
        }

        userService.register(user, password);
        throw new RedirectException("/index", "registrationDone");
    }

    private void action() {
        // No operations.
    }
}
