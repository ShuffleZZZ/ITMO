javac -cp ../artifacts/info.kgeorgiy.java.advanced.crawler.jar ru/ifmo/rain/glagolev/crawler/WebCrawler.java
java -p ../artifacts;../lib; -classpath . -m info.kgeorgiy.java.advanced.crawler easy ru.ifmo.rain.glagolev.crawler.WebCrawler %*
TIMEOUT /T -1