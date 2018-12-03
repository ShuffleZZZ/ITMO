package ru.itmo.webmail.model.repository;

import ru.itmo.webmail.model.domain.News;

import java.util.Queue;

public interface NewsRepository {
    void save(News news);
    Queue<News> findAll();
}