package ru.itmo.webmail.web.page;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

public class IndexPage extends Page {
    private void action(HttpServletRequest request, Map<String, Object> view) {
        // No operations.
    }

    private void registrationDone(HttpServletRequest request, Map<String, Object> view) {
        view.put("message", "You successfully registered, verify your email");
    }

    private void confirmationDone(HttpServletRequest request, Map<String, Object> view) {
        view.put("message", "Email successfully verified");
    }

    private void wrongInput(HttpServletRequest request, Map<String, Object> view) {
        view.put("message", "Wrong secret word, try again");
    }
}
