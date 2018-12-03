package ru.itmo.webmail.model.service;

import ru.itmo.webmail.model.domain.Article;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.exception.ValidationException;
import ru.itmo.webmail.model.repository.ArticleRepository;
import ru.itmo.webmail.model.repository.impl.ArticleRepositoryImpl;

import java.util.List;

public class ArticleService {
    private ArticleRepository articleRepository = new ArticleRepositoryImpl();

    public void validateArticleAdding(String title, String text) throws ValidationException {
        if (title == null || title.isEmpty()) {
            throw new ValidationException("Title is required");
        }
        if (title.length() < 3) {
            throw new ValidationException("Title cannot be shorter than 3 characters");
        }
        if (title.length() > 50) {
            throw new ValidationException("Title cannot be longer than 50 characters");
        }
        if (text == null || text.isEmpty()) {
            throw new ValidationException("Text is required");
        }
        if (text.length() > 255) {
            throw new ValidationException("Text cannot be longer than 255 characters");
        }
    }

    public void addArticle(User user, String title, String text, String hidden) {
        articleRepository.addArticle(user, title, text, hidden);
    }

    public List<ArticleRepositoryImpl.FrontArticle> findAllShowed() {
        return articleRepository.findAllShowed();
    }

    public List<Article> findByUser(User user) {
        return articleRepository.findByUser(user);
    }

    public void setShowing(Long articleId, boolean state) {
        articleRepository.setShowing(articleId, state);
    }

    public void validateChanging(Long articleId, Long userId) throws ValidationException {
        if (articleRepository.find(articleId) == null) {
            throw new ValidationException("Article doesn't exist");
        }

        if (!articleRepository.find(articleId).getUserId().equals(userId)) {
            throw new ValidationException("You are not the author");
        }
    }
}
