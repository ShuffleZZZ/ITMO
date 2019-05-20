javac -cp ../artifacts/info.kgeorgiy.java.advanced.student.jar ru/ifmo/rain/glagolev/student/*.java
java -p ../artifacts;../lib; -classpath . -m info.kgeorgiy.java.advanced.student StudentQuery ru.ifmo.rain.glagolev.student.StudentDB
TIMEOUT /T -1