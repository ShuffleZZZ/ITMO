package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.News;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.NewsRepository;
import ru.itmo.webmail.model.repository.impl.NewsRepositoryImpl;

import java.util.Queue;

public class NewsService {
    private NewsRepository newsRepository = new NewsRepositoryImpl();

    public void validateNews(String text, User user) throws ValidationException {
        if (user == null) {
            throw new ValidationException("Please, sign up to write");
        }
        if (text == null || text.equals("")) {
            throw new ValidationException("Please, enter the text");
        }
    }

    public void save(long id, String text){
        News news = new News();
        news.setUserID(id);
        news.setText(text);
        newsRepository.save(news);
    }

    public Queue<News> findAll() {
        return newsRepository.findAll();
    }
}
