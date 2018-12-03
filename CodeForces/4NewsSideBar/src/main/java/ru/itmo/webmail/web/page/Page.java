package ru.itmo.webmail.web.page;

import ru.itmo.webmail.model.domain.NewsAndUser;
import ru.itmo.webmail.model.domain.News;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.service.NewsService;
import ru.itmo.webmail.model.service.UserService;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public abstract class Page {
    UserService userService = new UserService();
    NewsService newsService = new NewsService();

    public void after(Map<String, Object> view) {
        List<NewsAndUser> result = new ArrayList<>();
        for (News n: newsService.findAll()) {
            result.add(new NewsAndUser(n));
        }
        view.put("news", result);
    }

    public void before(HttpServletRequest request, Map<String, Object> view) {
        view.put("userCount", userService.findCount());
        User user = (User) request.getSession().getAttribute("user");
        if (user != null) {
            view.put("authorized", true);
            view.put("username", user.getLogin());
        }
        view.put("news", newsService.findAll());
    }
}