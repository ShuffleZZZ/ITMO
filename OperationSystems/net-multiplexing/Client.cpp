#include <iostream>
#include <cstring>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>

const unsigned int BUFFER_SIZE = 1024, DEFAULT_PORT = 8080, MAX_EVENTS = 64;

int getNumericValue(std::string value)
{
    bool error = 0;
    int result = 0;
    for (char c : value) {
        if (c < 48 || c > 57)
        {
            error = 1;
            break;
        }
        result *= 10;
        result += c - 48;
    }
    if (error)
    {
        std::cout << "Wrong input: expected correct digit, not " << value << '\n';
        exit(0);
    }
    return result;
}

void closeAll(int epoll, int curSocket)
{
    if (close(epoll) == -1)
    {
        std::cout << "Error occurred while closing the epoll\n";
        exit(-1);
    }
    if (close(curSocket) == -1)
    {
        std::cout << "Error occurred while closing the socket\n";
        exit(-1);
    }
}

int main(int argc, char* argv[], char *envp[])
{
    if (argc > 2)
    {
        std::cout << "Wrong input: expected port or no arguments\n";
        return 0;
    }
    int curSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (curSocket == -1)
    {
        std::cout << "Unable to create a socket\n";
        return -1;
    }
    int epoll = epoll_create1(0);
    if (epoll == -1)
    {
        std::cout << "Unable to create epoll\n";
        if (close(curSocket) == -1)
        {
            std::cout << "Error occurred while closing the socket\n";
            return -1;
        }
        return -1;
    }
    int port = DEFAULT_PORT;
    if (argc == 2)
    {
        port = getNumericValue(argv[1]);
    }
    struct epoll_event curClient, clients[MAX_EVENTS];
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(curSocket, (sockaddr*) &address, sizeof(address)) == -1)
    {
        std::cout << "Unable to connect client socket\n";
        closeAll(epoll, curSocket);
        return -1;
    }
    curClient.events = EPOLLIN;
    curClient.data.fd = curSocket;
    if (epoll_ctl(epoll, EPOLL_CTL_ADD, curSocket, &curClient) == -1)
    {
        std::cout << "Unable to add current client to epoll\n";
        closeAll(epoll, curSocket);
        return -1;
    }
    curClient.data.fd = 0;
    if (epoll_ctl(epoll, EPOLL_CTL_ADD, 0, &curClient) == -1)
    {
        std::cout << "Unable to add current client to epoll\n";
        closeAll(epoll, curSocket);
        return -1;
    }
    char response[BUFFER_SIZE] = {};
    int messageSize = 0;
    std::cout << "Connected. Type in the message\n";
    while (true)
    {
        if (feof(stdin))
        {
            std::cout << '\n';
            closeAll(epoll, curSocket);
            return -1;
        }
        int clientsAmount = epoll_wait(epoll, clients, MAX_EVENTS, -1);
        if (clientsAmount == -1)
        {
            std::cout << "Error occurred during epoll waiting\n";
            closeAll(epoll, curSocket);
            return -1;
        }
        for (int i = 0; i < clientsAmount; ++i)
        {
            if (clients[i].data.fd == curSocket)
            {
                int requestSize = 0;
                std::cout << "Response is: ";
                while (requestSize < messageSize)
                {
                    int received = recv(curSocket, response, BUFFER_SIZE, 0);
                    if (received == -1 || received == 0)
                    {
                        std::cout << "Error occurred while receiving a message\n";
                        closeAll(epoll, curSocket);
                        return -1;
                    }
                    requestSize += received;
                    for (int i = 0; i < received; ++i)
                    {
                        std::cout << response[i];
                    }
                }
                std::cout << '\n';
            } else {
                std::cin >> response;
                messageSize = strlen(response);
                int responseSize = 0;
                while (responseSize < messageSize)
                {
                    int sended = send(curSocket, response + responseSize, messageSize - responseSize, 0);
                    if (sended == -1)
                    {
                        std::cout << "Error occurred on sending the message\n";
                        closeAll(epoll, curSocket);
                        return -1;
                    }
                    responseSize += sended;
                }
            }
        }
    }
    closeAll(epoll, curSocket);
    return 0;
}
