package ru.itmo.wp.servlet;

import com.google.gson.Gson;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.ArrayList;

public class MessagesServlet extends HttpServlet {
    class messages {
        public messages(String name, String msg) {
            user = name;
            text = msg;
        }
        public String user, text;
    }
    private ArrayList<messages> Messages = new ArrayList<>();
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");
        switch (request.getRequestURI()) {
            case "/message/auth":
                auth(request, response);
                break;
            case "/message/add":
                add(request);
                break;
            case "/message/findAll":
                findAll(response);
                break;
        }
    }

    private void auth(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        String input = request.getParameter("user");
        if (input != null) {
            session.setAttribute("user", input);
        } else input = "";
        String json = new Gson().toJson(input);
        response.getWriter().print(json);
        response.getWriter().flush();
    }

    private void add(HttpServletRequest request) {
        String input = request.getParameter("text");
        Messages.add(new messages(request.getSession().getAttribute("user").toString(), input));
    }

    private void findAll(HttpServletResponse response) throws IOException {
        String json = new Gson().toJson(Messages);
        response.getWriter().print(json);
        response.getWriter().flush();
    }
}
