package ru.ifmo.rain.glagolev.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class HelloUDPServer implements HelloServer {
    private ExecutorService stream = null;
    private Semaphore amount = null;
    private DatagramSocket socket = null;

    public HelloUDPServer() {}

    public static void main(String[] args) {
        if (args.length < 2 || args[0] == null || args[1] == null) {
            System.out.println("Wrong input: 5 non-null arguments expected");
            return;
        }
        HelloUDPServer server = new HelloUDPServer();
        try {
            server.start(Integer.valueOf(args[0]), Integer.valueOf(args[1]));
        } catch (NumberFormatException e) {
            System.out.println("Wrong input: expected integer, found: " + e.getMessage());
        }
    }

    @Override
    public void start(int port, int streamsAmount) {
        stream = Executors.newFixedThreadPool(streamsAmount + 1);
        amount = new Semaphore(streamsAmount);
        int packetSize;
        try {
            socket = new DatagramSocket(port);
            packetSize = socket.getSendBufferSize();
        } catch (SocketException e) {
            return;
        }
        stream.submit(() -> {
            while (!Thread.currentThread().isInterrupted()) {
                final byte[] request = new byte[packetSize];
                final DatagramPacket receivePacket = new DatagramPacket(request, packetSize);
                try {
                    socket.receive(receivePacket);
                } catch (IOException e) {
                    continue;
                }
                final InetAddress clientAddress = receivePacket.getAddress();
                final int clientPort = receivePacket.getPort();
                final String requestString = new String(request, 0, receivePacket.getLength(), StandardCharsets.UTF_8);
                try {
                    amount.acquire();
                } catch (InterruptedException ignored) {
                    //
                }
                stream.submit(() -> {
                    String responseString = "Hello, " + requestString;
                    byte[] response = responseString.getBytes(StandardCharsets.UTF_8);
                    DatagramPacket sendPacket = new DatagramPacket(response, response.length, clientAddress, clientPort);
                    try {
                        socket.send(sendPacket);
                    } catch (IOException ignored) {
                        //
                    }
                    amount.release();
                });
            }
        });
    }

    @Override
    public void close() {
        if (socket != null) {
            socket.close();
        }
        stream.shutdownNow();
        try {
            stream.awaitTermination(5, TimeUnit.SECONDS);
        } catch (InterruptedException ignored) {
            //
        }
    }
}
