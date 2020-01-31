import grammar.GoodImpLangLexer;
import grammar.GoodImpLangParser;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Main {
    public static void main(String[] args) throws IOException {
        CharStream charStream = CharStreams.fromStream(new FileInputStream("test/main.gil"));
        GoodImpLangLexer lexer = new GoodImpLangLexer(charStream);
        GoodImpLangParser parser = new GoodImpLangParser(new CommonTokenStream(lexer));
        GoodImpLangVisitor visitor = new GoodImpLangVisitor();

        Path outputFile = Paths.get(System.getProperty("user.dir") +
                                        File.separator + "test" +
                                            File.separator + "main.c");

        try (BufferedWriter writer = Files.newBufferedWriter(outputFile, StandardCharsets.UTF_8)) {
            writer.write(visitor.visit(parser.program()));
        } catch (IOException e) {
            System.out.println("Unable to write to file: " + e.getMessage());
        }
    }
}

