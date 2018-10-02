import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Formatter;
import java.net.URLDecoder;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

class HttpServer {
    private final File root;

    private HttpServer(File root, int port) throws IOException {
        this.root = root;

        ServerSocket serverSocket = new ServerSocket(port);
        while (serverSocket.isBound()) {
            try {
                Socket socket = serverSocket.accept();
                process(socket);
                socket.close();
            } catch (IOException ignored) {
                // No operations.
            }
        }
    }

    private void process(Socket socket) throws IOException {
        Request request = readRequest(socket);

        Response response = new Response();
        response.setHeader("Connection", "close");

        try {
            process(request, response);
        } catch (Exception ignored) {
            response.setStatusCode(502);
        }

        try {
            writeResponse(socket, response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void writeResponse(Socket socket, Response response) throws IOException {
        try {
            ByteArrayOutputStream result = new ByteArrayOutputStream();
            result.write(("HTTP/1.1 " + response.getStatusCode() + " NA\r\n").getBytes());
            for (Map.Entry<String, String> entry : response.getHeaders().entrySet()) {
                result.write((entry.getKey() + ": " + entry.getValue() + "\r\n").getBytes());
            }
            result.write("\r\n".getBytes());
            if (response.getBody() != null) {
                result.write(response.getBody());
            }

            OutputStream outputStream = socket.getOutputStream();
            outputStream.write(result.toByteArray());
            outputStream.close();
        } finally {
            socket.close();
        }
    }

    private void process(Request request, Response response) throws IOException, NoSuchAlgorithmException {
        if (!"GET".equals(request.getMethod())) {
            response.setStatusCode(405);
            return;
        }

        File file = new File(root, request.getUri());
        if (file.isFile()) {
            byte[] body = readFile(file);
            String etag = getEtag(body);
            if(request.getHeader("If-None-Match").equals(etag)){
                response.setStatusCode(304);
            }
            else {
                response.setStatusCode(200);
                response.setBody(body);
                response.setHeader("Content-Length", Integer.toString(body.length));
                response.setHeader("Content-Type", getContentType(file));
            }
            response.setHeader("ETag",etag);
        } else {
            response.setStatusCode(404);
        }
    }

    private String getContentType(File file) {
        String path = file.getAbsolutePath();
        if (path.endsWith(".html") || path.endsWith(".htm")) {
            return "text/html";
        }
        if (path.endsWith(".png")){
            return "image/png";
        }
        throw new IllegalArgumentException();
    }

    private void silentClose(Closeable closeable) {
        try {
            closeable.close();
        } catch (Exception ignored) {
            // No operations.
        }
    }

    private byte[] readInputStream(InputStream inputStream, boolean breakOnCrLf) throws IOException {
        ByteArrayOutputStream bytes = new ByteArrayOutputStream();

        byte[] lastTwoBytes = new byte[2];
        int lastTwoBytesSize = 0;

        try {
            byte[] buffer = new byte[1024];
            while (true) {
                if (breakOnCrLf && lastTwoBytes[0] == 13 && lastTwoBytes[1] == 10) {
                    break;
                }

                int read = inputStream.read(buffer);
                if (breakOnCrLf) {
                    if (read == 1) {
                        if (lastTwoBytesSize > 1) {
                            lastTwoBytes[0] = lastTwoBytes[1];
                        }
                        lastTwoBytesSize = Math.max(0, lastTwoBytesSize - 1);
                        lastTwoBytes[lastTwoBytesSize++] = buffer[read - 1];
                    } else if (read >= 2) {
                        lastTwoBytesSize = 2;
                        lastTwoBytes[0] = buffer[read - 2];
                        lastTwoBytes[1] = buffer[read - 1];
                    }
                }

                if (read >= 0) {
                    bytes.write(buffer, 0, read);
                } else {
                    break;
                }
            }
        } finally {
            silentClose(bytes);
        }

        return bytes.toByteArray();
    }

    private byte[] readFile(File file) throws IOException {
        InputStream inputStream = new FileInputStream(file);
        try {
            return readInputStream(inputStream, false);
        } finally {
            silentClose(inputStream);
        }
    }

    private Request readRequest(Socket socket) throws IOException {
        InputStream inputStream = socket.getInputStream();
        return new Request(new String(readInputStream(inputStream, true)));
    }

    private static final class Request {
        private final String method;
        private String uri;
        private final Map<String, String> headers;

        private Request(String request) throws UnsupportedEncodingException {
            String[] lines = request.split("[\r\n]+");
            if (lines.length < 1) {
                throw new IllegalArgumentException();
            }

            String[] firstLineTokens = lines[0].split("\\s+");
            method = firstLineTokens[0];
            uri = firstLineTokens[1];
            if(!uri.endsWith(".htm")&&!uri.endsWith(".html")&&!uri.endsWith(".png")){
                uri=uri+"/index.html";
            }
            uri= URLDecoder.decode(uri,"UTF-8");
            headers = new HashMap<>();

            for (int i = 1; i < lines.length; i++) {
                String line = lines[i];
                if (line.contains(":")) {
                    int sep = line.indexOf(':');
                    headers.put(line.substring(0, sep), line.substring(sep + 1).trim());
                }
            }
        }

        private String getMethod() {
            return method;
        }

        private String getUri() {
            return uri;
        }

        @SuppressWarnings({"SameParameterValue", "unused"})
        private String getHeader(String name) {
            if(headers.containsKey("If-None-Match")){
                return headers.get("If-None-Match");
            }
            return "";
        }
    }

    private static final class Response {
        private int statusCode;
        private final Map<String, String> headers = new HashMap<>();
        private byte[] body;

        private void setHeader(String name, String value) {
            headers.put(name, value);
        }

        private int getStatusCode() {
            return statusCode;
        }

        private void setStatusCode(int statusCode) {
            this.statusCode = statusCode;
            this.body = ("Error " + statusCode).getBytes();
        }

        private byte[] getBody() {
            return body;
        }

        private void setBody(byte[] body) {
            this.body = body;
        }

        private Map<String, String> getHeaders() {
            return Collections.unmodifiableMap(headers);
        }
    }

    private static String getEtag(byte[] body) throws NoSuchAlgorithmException {
        Formatter code=new Formatter();
        for(byte b:MessageDigest.getInstance("SHA-256").digest(body)){
            code.format("%02x",b);
        }
        return code.toString();
    }

    public static void main(String[] args) throws IOException {
        new HttpServer(new File("static"), 8088);
    }
}
