package ru.ifmo.rain.glagolev.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class HelloUDPClient implements HelloClient {
    private static final int TIMEOUT = 1000;
    private final int MAX_REQUESTS = 10;

    public HelloUDPClient() {}

    public static void main(String[] args) {
        if (args.length < 5 || Arrays.asList(args).contains(null)) {
            System.out.println("Wrong input: 5 non-null arguments expected");
            return;
        }
        HelloUDPClient client = new HelloUDPClient();
        try {
            client.run(args[0], Integer.valueOf(args[1]), args[2], Integer.valueOf(args[3]), Integer.valueOf(args[4]));
        } catch (NumberFormatException e) {
            System.out.println("Wrong input: expected integer, found: " + e.getMessage());
        }
    }
    @Override
    public void run(String host, int port, String prefix, int streamsAmount, int capacity) {
        ExecutorService[] streams = new ExecutorService[streamsAmount];
        for (int i = 0; i < streamsAmount; i++) {
            streams[i] = Executors.newSingleThreadExecutor();
        }
        final InetAddress address;
        try {
            address = InetAddress.getByName(host);
        } catch (UnknownHostException e) {
            System.out.println("Wrong host address: " + e.getMessage());
            return;
        }
        for (int i = 0; i < streamsAmount; i++) {
            ExecutorService stream = streams[i];
            final int ind = i;
            stream.submit(() -> {
                for (int j = 0; j < capacity; j++) {
                    final DatagramSocket socket;
                    int packetSize;
                    try {
                        socket = new DatagramSocket();
                        socket.setSoTimeout(TIMEOUT);
                        packetSize = socket.getReceiveBufferSize();
                    } catch (SocketException e) {
                        return;
                    }
                    String requestString = prefix + ind + "_" + j;
                    byte[] request = requestString.getBytes(StandardCharsets.UTF_8);
                    byte[] response = new byte[packetSize];
                    DatagramPacket sendPacket = new DatagramPacket(request, request.length, address, port);
                    for (int k = 0; k < MAX_REQUESTS; ++k) {
                        try {
                            socket.send(sendPacket);
                            DatagramPacket recievePacket = new DatagramPacket(response, packetSize);
                            socket.receive(recievePacket);
                            String input = new String(response, 0, recievePacket.getLength(), StandardCharsets.UTF_8);
                            if (input.contains(requestString)) {
                                System.out.println(input);
                            } else {
                                continue;
                            }
                        } catch (IOException e) {
                            continue;
                        }
                        break;
                    }
                }
            });
        }
        Arrays.stream(streams).forEach(ExecutorService::shutdown);
        Arrays.stream(streams).forEach(stream -> {
            try {
                stream.awaitTermination(streamsAmount * capacity * 10, TimeUnit.SECONDS);
            } catch (InterruptedException ignored) {
                //
            }
        });
    }
}
