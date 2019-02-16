package ru.ifmo.rain.glagolev.walk;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Walk {
    private final static int FNV_PRIME = 0x01000193;
    private final static int FNV_FIRST = 0x811c9dc5;
    private final static int FNV_BYTES = 1024;
    private final static int FNV_BITMASK = 0xff;

    public static void main(String[] args) {
        if (args != null && args.length == 2) {
            if (args[0] != null && args[1] != null) {
                printHashes(args[0], args[1]);
            } else {
                System.out.println("Input error: non-null files expected");
            }
        } else {
            System.out.println("Input error: 2 files expected");
        }
    }

    private static void printHashes(String in, String out) {
        Path inputPath;
        Path outputPath;
        try {
            inputPath = Paths.get(in);
            outputPath = Paths.get(out);
        } catch (InvalidPathException e) {
            System.out.println("Incorrect path error");
            return;
        }
        if (outputPath.getParent() != null) {
            try {
                Files.createDirectories(outputPath.getParent());
            } catch (IOException e) {
                System.out.println("Couldn't create output file path");
                return;
            }
        }
        try (BufferedReader reader = Files.newBufferedReader(inputPath)) {
            try (BufferedWriter writer = Files.newBufferedWriter(outputPath)) {
                String inputFile;
                while ((inputFile = reader.readLine()) != null) {
                    try {
                        Path path = Paths.get(inputFile);
                        writer.write(String.format("%08x %s", countFNV(path), inputFile));
                        writer.newLine();
                    } catch (InvalidPathException e) {
                        writer.write("00000000 " + inputFile);
                        writer.newLine();
                    }
                }
            } catch (IOException e) {
                System.out.println("Output file error: " + e.getMessage());
                return;
            }
        } catch (IOException e) {
            System.out.println("Input file error: " + e.getMessage());
            return;
        }
    }

    private static int countFNV(Path path) {
        int hval = FNV_FIRST;
        try (FileInputStream inputStream = new FileInputStream(path.toString())) {
            int input;
            byte[] temp = new byte[FNV_BYTES];
            while ((input = inputStream.read(temp)) != -1) {
                for (int i = 0; i < input; ++i) {
                    hval *= FNV_PRIME;
                    hval ^= temp[i] & FNV_BITMASK;
                }
            }
        } catch (IOException e) {
            hval = 0;
        }
        return hval;
    }
}