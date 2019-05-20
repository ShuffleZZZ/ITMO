javac -cp ../artifacts/info.kgeorgiy.java.advanced.mapper.jar ru/ifmo/rain/glagolev/mapper/ParallelMapperImpl.java
javac -cp ../artifacts/info.kgeorgiy.java.advanced.concurrent.jar;../artifacts/info.kgeorgiy.java.advanced.mapper.jar ru/ifmo/rain/glagolev/mapper/IterativeParallelism.java
java -p ../artifacts;../lib; -classpath . -m info.kgeorgiy.java.advanced.mapper scalar ru.ifmo.rain.glagolev.mapper.ParallelMapperImpl,ru.ifmo.rain.glagolev.mapper.IterativeParallelism %*
TIMEOUT /T -1