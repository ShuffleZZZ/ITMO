package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.Article;
import ru.itmo.webmail.model.domain.User;
import ru.itmo.webmail.model.repository.impl.ArticleRepositoryImpl;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.List;

public interface ArticleRepository {
    void addArticle(User user, String title, String text, String hidden);
    List<ArticleRepositoryImpl.FrontArticle> findAllShowed();
    List<Article> findByUser(User user);
    void setShowing(Long articleId, boolean state);
    Article find(Long id);
}
