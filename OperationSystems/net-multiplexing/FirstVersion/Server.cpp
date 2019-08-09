#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <fcntl.h>

const unsigned int BUFFER_SIZE = 1024, DEFAULT_PORT = 8080;
const char* TERMINATION_STRING = "Good bye\n";
const char* WELCOME_STRING = "Connected to server\n";

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
        std::cout << "Wrong input: just port expected\n";
        return 0;
    }
    int curSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (curSocket == -1)
    {
        std::cout << "Unable to create a socket\n";
        return -1;
    }
    int opt = 1;
    if (setsockopt(curSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        std::cout << "Unable to set socket's options\n";
        if (close(curSocket) == -1)
        {
            std::cout << "Error occurred while closing the socket\n";
        }
        return -1;
    }
    if (fcntl(curSocket, F_SETFL, fcntl(curSocket, F_GETFD, 0) | O_NONBLOCK) == -1)
    {
        std::cout << "Unable to make socket unblocked\n";
        if (close(curSocket) == -1)
        {
            std::cout << "Error occurred while closing the socket\n";
        }
        return -1;
    }
    int port = DEFAULT_PORT;
    if (argc == 2)
    {
        port = getNumericValue(argv[1]);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(curSocket, (sockaddr*) &address, sizeof(address)) == -1)
    {
        std::cout << "Unable to bind to socket\n";
        if (close(curSocket) == -1)
        {
            std::cout << "Error occurred while closing the socket\n";
        }
        return -1;
    }
    if (listen(curSocket, 1) == -1)
    {
        std::cout << "Unable to set listening for socket\n";
        if (close(curSocket) == -1)
        {
            std::cout << "Error occurred while closing the socket\n";
        }
        return -1;
    }
    int epoll = epoll_create(BUFFER_SIZE);
    if (epoll == -1)
    {
        std::cout << "Unable to create epoll\n";
        if (close(curSocket) == -1)
        {
            std::cout << "Error occurred while closing the socket\n";
        }
        return -1;
    }
    static struct epoll_event curClient, clients[BUFFER_SIZE];
    curClient.events = EPOLLIN | EPOLLET;
    curClient.data.fd = curSocket;
    if (epoll_ctl(epoll, EPOLL_CTL_ADD, curSocket, &curClient) == -1)
    {
        std::cout << "Unable to add current client to epoll\n";
        closeAll(epoll, curSocket);
        return -1;
    }
    while (true)
    {
        int clientsAmount = epoll_wait(epoll, clients, BUFFER_SIZE, -1);
        if (clientsAmount == -1)
        {
            std::cout << "Error occurred during epoll waiting\n";
            closeAll(epoll, curSocket);
            return -1;
        }
        for (unsigned int i = 0; i < clientsAmount; ++i)
        {
            if (clients[i].data.fd == curSocket)
            {
                int client = accept(curSocket, nullptr, nullptr);
                if (client == -1)
                {
                    std::cout << "Error during receiving request from client\n";
                    continue;
                }
                std::cout << "Client \"" << client << "\" connected\n";
                if (fcntl(client, F_SETFL, fcntl(client, F_GETFD, 0) | O_NONBLOCK) == -1)
                {
                    std::cout << "Unable to make socket unblocked\n";
                    continue;
                }
                curClient.data.fd = client;
                if (epoll_ctl(epoll, EPOLL_CTL_ADD, client, &curClient) == -1)
                {
                    std::cout << "Unable to add current client to epoll\n";
                    continue;
                }
                if (send(client, WELCOME_STRING, BUFFER_SIZE, 0) == -1)
                {
                    std::cout << "Error occurred on sending the message\n";
                }
            } else {
                char request[BUFFER_SIZE] = {};
                ssize_t requestSize = recv(clients[i].data.fd, request, BUFFER_SIZE, 0);
                if (requestSize == -1)
                {
                    std::cout << "Error occurred while receiving a message\n";
                    continue;
                }
                if (strncmp(request, "shutdown", requestSize) == 0)
                {
                    if (send(clients[i].data.fd, TERMINATION_STRING, strlen(TERMINATION_STRING), 0) == -1)
                    {
                        std::cout << "Error occurred on sending the message\n";
                    }
                    std::cout << "Server has been shut down by client\n";
                    for (unsigned int j = 0; j <= i; ++j)
                    {
                        if (close(clients[j].data.fd) == -1)
                        {
                            std::cout << "Error occurred while closing the client socket\n";
                        }
                    }
                    closeAll(epoll, curSocket);
                    return 0;
                } else if (strncmp(request, "disconnect", requestSize) == 0) {
                    if (send(clients[i].data.fd, TERMINATION_STRING, strlen(TERMINATION_STRING), 0) == -1)
                    {
                        std::cout << "Error occurred on sending the message\n";
                    }
                    std::cout << "Client \"" << clients[i].data.fd << "\" disconnected\n";
                    if (close(clients[i].data.fd) == -1)
                    {
                        std::cout << "Error occurred while closing the client socket\n";
                    }
                } else {
                    for (int i = 0; i < requestSize / 2; ++i)
                    {
                        char temp = request[i];
                        request[i] = request[requestSize - 1 - i];
                        request[requestSize - 1 - i] = temp;
                    }
                    if (send(clients[i].data.fd, request, requestSize, 0) == -1)
                    {
                        std::cout << "Error occurred on sending the message\n";
                    }
                }
            }
        }
    }
    closeAll(epoll, curSocket);
    return 0;
}
