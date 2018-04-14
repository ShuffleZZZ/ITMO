package Hash;

import java.io.*;
import java.security.MessageDigest;
import java.nio.file.*;

public class CalcSHA256 {
    public static void main(String[] args) throws Exception {
        BufferedReader files = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), "UTF8"));
        String S;
        try {
            S = files.readLine();
        } catch (NullPointerException e) {
            return;
        }
        while (S != null) {
            MessageDigest digit = MessageDigest.getInstance("SHA-256");
            for (byte RES : digit.digest(Files.readAllBytes(Paths.get(S)))) {
                System.out.printf("%02X", RES);
            }
            System.out.println();
            S = files.readLine();
        }
    }
}