package ru.itmo.webmail.model.repository.impl;

import ru.itmo.webmail.model.domain.News;
import ru.itmo.webmail.model.repository.NewsRepository;

import java.io.*;
import java.util.Queue;
import java.util.LinkedList;

public class NewsRepositoryImpl implements NewsRepository {
    private static final File tmpDir = new File(System.getProperty("java.io.tmpdir"));
    private Queue<News> news;

    public NewsRepositoryImpl() {
        try {
            //noinspection unchecked
            news = (Queue<News>) new ObjectInputStream(
                    new FileInputStream(new File(tmpDir, getClass().getSimpleName()))).readObject();
        } catch (Exception e) {
            news = new LinkedList<>();
        }
    }

    @Override
    public void save(News post) {
        news.add(post);

        try {
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(
                    new FileOutputStream(new File(tmpDir, getClass().getSimpleName())));
            objectOutputStream.writeObject(news);
            objectOutputStream.close();
        } catch (Exception e) {
            throw new RuntimeException("Can't save news.", e);
        }
    }

    @Override
    public Queue<News> findAll() {
        return new LinkedList<>(news);
    }

}