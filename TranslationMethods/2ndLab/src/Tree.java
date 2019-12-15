import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Tree {
    private final String node;
    private final List<Tree> children;

    Tree(String node, Tree... children) {
        this.node = node;
        this.children = Arrays.asList(children);
    }

    Tree(String node) {
        this.node = node;
        this.children = new ArrayList<>();
    }

    void print(int testNumber) {
        final String outDir = System.getProperty("user.dir") + File.separator + "ParseTree";
        Path outputFile = Paths.get(outDir + File.separator + "ParseTree" + testNumber + ".html");

        if (outputFile.getParent() != null) {
            try {
                Files.createDirectories(outputFile.getParent());
            } catch (IOException e) {
                System.out.println("Couldn't create output file path");
                return;
            }
        }

        try (BufferedWriter writer = Files.newBufferedWriter(outputFile, StandardCharsets.UTF_8)) {
            final String htmlFileStart = "<!DOCTYPE html><html lang=\"ru\"><head><meta charset=\"utf-8\">" +
                    "<title>Parse tree</title><link rel=\"stylesheet\" href=\"./ParseTree.css\"></head>" +
                    "<body><div class=\"tree\"><ul>";
            final String htmlFileEnd = "</ul></div></body>";

            writer.write(htmlFileStart);
            printNode(writer);
            writer.write(htmlFileEnd);
        } catch (IOException e) {
            System.out.println("Unable to write to file: " + e.getMessage());
        }
    }

    private void printNode(BufferedWriter writer) throws IOException {
        final String htmlNodeStart = "<li><a href=\"#\">" + node + "</a>";
        final String htmlNodeEnd = "</li>";

        writer.write(htmlNodeStart);

        if (!children.isEmpty()) {
            writer.write("<ul>");
            for (Tree child : children) {
                child.printNode(writer);
            }
            writer.write("</ul>");
        }

        writer.write(htmlNodeEnd);
    }
}