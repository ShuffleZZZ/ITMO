package ru.ifmo.rain.glagolev.crawler;

import info.kgeorgiy.java.advanced.crawler.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Phaser;

/**
 * Downloads all of the pages within the given depth from the starting URL, using multithreading.
 */
public class WebCrawler implements Crawler {
    private final ExecutorService downloaders;
    private final ExecutorService extractors;
    private final Downloader downloader;

    /**
     * Default constructor.
     */
    public WebCrawler() {
        this((Downloader) null, 0, 0, 0);
    }

    /**
     * Constructor with given parameters.
     *
     * @param downloader  {@link Downloader}.
     * @param downloaders maximum amount of pages to download at one time.
     * @param extractors  maximum amount of pages to extract links.
     * @param perHost     maximum amount of pages to download from 1 host.
     */
    public WebCrawler(Downloader downloader, int downloaders, int extractors, int perHost) {
        this.downloaders = Executors.newFixedThreadPool(downloaders);
        this.extractors = Executors.newFixedThreadPool(extractors);
        this.downloader = downloader;
    }

    /**
     * The entry point, which executes program with given parameters.
     *
     * @param args Expected starting {@link java.net.URL},
     *             depth,
     *             amount of downloaders,
     *             amount of extractors
     *             and maximum downloads from 1 host.
     * @throws IOException May occur while creating {@link Downloader}.
     */
    public static void main(String[] args) throws IOException {
        if (args.length != 5 || args[0] == null) {
            System.out.println("Input error: wrong number of arguments or illegal arguments");
            return;
        }
        int depth, downloaders, extractors, perHost;
        try {
            depth = Integer.parseInt(args[1]);
            downloaders = Integer.parseInt(args[2]);
            extractors = Integer.parseInt(args[3]);
            perHost = Integer.parseInt(args[4]);
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Expected integer value, not: ", e);
        }
        Downloader downloader = new CachingDownloader();
        WebCrawler crawler = new WebCrawler(downloader, downloaders, extractors, perHost);
        String url = args[0];
        Result result = crawler.download(url, depth);
        System.out.println(result.getDownloaded().size() + " pages were successfully downloaded:"
                + System.lineSeparator());
        result.getDownloaded().forEach(System.out::println);
        System.out.println(result.getErrors().size() + " errors occurred:" + System.lineSeparator());
        result.getErrors().forEach((s, e) -> {
            System.out.println("URL: " + s);
            System.out.println("Error: " + e.getMessage());
        });
    }

    /**
     * {@inheritDoc}
     *
     * @param url   Starting url.
     * @param depth Depth of crawling.
     * @return All the downloaded pages and errors of not downloaded ones.
     */
    @Override
    public Result download(String url, int depth) {
        final Set<String> result = ConcurrentHashMap.newKeySet();
        final Map<String, IOException> errors = new ConcurrentHashMap<>();
        final Phaser phaser = new Phaser(1);
        result.add(url);
        crawl(url, depth, result, errors, phaser);
        phaser.arriveAndAwaitAdvance();
        result.removeAll(errors.keySet());
        return new Result(new ArrayList<>(result), errors);
    }

    /**
     * Crawler, which handles all URLs within given depth from the first one.
     *
     * @param url      current {@link java.net.URL} to download and extract links.
     * @param depth    depth needed from this exact {@link java.net.URL} furthermore.
     * @param vistited {@link java.net.URL URLs} which already processed.
     * @param errors   {@link Map} of failed downloaded {@link java.net.URL URLs} and their
     *                 {@link Exception Exceptions}.
     * @param phaser   {@link Phaser} to synchronize.
     */
    private void crawl(final String url, final int depth, final Set<String> vistited,
                       final Map<String, IOException> errors, final Phaser phaser) {
        if (depth > 0) {
            Runnable downloadTask = () -> {
                try {
                    final Document document = downloader.download(url);
                    Runnable extractTask = () -> {
                        try {
                            for (String link : document.extractLinks()) {
                                if (vistited.add(link)) {
                                    crawl(link, depth - 1, vistited, errors, phaser);
                                }
                            }
                        } catch (IOException e) {
                            errors.put(url, e);
                        } finally {
                            phaser.arrive();
                        }
                    };
                    if (depth > 1) {
                        phaser.register();
                        extractors.submit(extractTask);
                    }
                } catch (IOException e) {
                    errors.put(url, e);
                } finally {
                    phaser.arrive();
                }
            };
            phaser.register();
            downloaders.submit(downloadTask);
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void close() {
        downloaders.shutdownNow();
        extractors.shutdownNow();
    }
}