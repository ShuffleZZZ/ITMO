package Hash;

import java.io.*;
import java.security.MessageDigest;
import java.nio.file.*;

public class CalcMD5 {
    public static void main(String[] args) throws Exception {
        BufferedReader files = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), "UTF8"));
        String Str;
        try {
            Str = files.readLine();
        } catch (NullPointerException e) {
            return;
        }
        while (Str!=null) {
            MessageDigest DIGIT = MessageDigest.getInstance("MD5");
            for (byte RES : DIGIT.digest(Files.readAllBytes(Paths.get(Str)))) {
                System.out.printf("%02X", RES);
            }
            System.out.println();
            Str = files.readLine();
        }
    }
}