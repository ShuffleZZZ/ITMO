package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.User;

import javax.servlet.http.HttpServletRequest;
import java.util.*;

public class IndexPage extends Page {
    private void action() {
    }

    private void registrationDone(Map<String, Object> view) {
        view.put("message", "You have been registered");
    }

    private void enterDone(HttpServletRequest request, Map<String, Object> view) {
        view.put("message", "Welcome, " + ((User) request.getSession().getAttribute("user")).getLogin());
    }

    private void logout(Map<String, Object> view) {
        view.put("message", "You have been logged out");
    }

    private void newsAdded(Map<String, Object> view) {
        view.put("message", "You successfully posted news");
    }
}