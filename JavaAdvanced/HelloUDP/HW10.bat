javac -cp ../artifacts/info.kgeorgiy.java.advanced.hello.jar ru/ifmo/rain/glagolev/hello/*.java
java -p ../artifacts;../lib; -classpath . -m info.kgeorgiy.java.advanced.hello client-i18n ru.ifmo.rain.glagolev.hello.HelloUDPClient
java -p ../artifacts;../lib; -classpath . -m info.kgeorgiy.java.advanced.hello server-i18n ru.ifmo.rain.glagolev.hello.HelloUDPServer
TIMEOUT /T -1