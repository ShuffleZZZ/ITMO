#include <iostream>

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
        std::cout << "Wrong input: just port expected\n";
        return 0;
    }
    int curSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (curSocket == -1)
    {
        std::cout << "Unable to create a socket\n";
        return -1;
    }
    int epoll = epoll_create1(0);
    if (epoll == -1)
    {
        std::cout << "Unable to create epoll\n";
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
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(curSocket, (sockaddr*) &address, sizeof(address)) == -1)
    {
        std::cout << "Unable to bind to socket\n";
        return -1;
    }
    if (listen(curSocket, 5) == -1)
    {
        std::cout << "Unable to set listening for socket\n";
        return -1;
    }
    curClient.events = EPOLLIN;
    curClient.data.fd = curSocket;
    if (epoll_ctl(epoll, EPOLL_CTL_ADD, curSocket, &curClient) == -1)
    {
        std::cout << "Unable to add to epoll\n";
        closeAll(epoll, curSocket);
        return -1;
    }
    std::cout << "Server is up\n";
    while (true)
    {
        int clientsAmount = epoll_wait(epoll, clients, MAX_EVENTS, -1);
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
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                int code = accept(curSocket, (sockaddr*) &client, &len);
                if (code == -1)
                {
                    std::cout << "Error during receiving request from client\n";
                    continue;
                }
                std::cout << "Client \"" << code << "\" connected\n";
                curClient.events = EPOLLIN;
                curClient.data.fd = code;
                if (epoll_ctl(epoll, EPOLL_CTL_ADD, code, &curClient) == -1)
                {
                    std::cout << "Unable to add to epoll\n";
                    closeAll(epoll, curSocket);
                    return -1;
                }
            } else {
                char request[BUFFER_SIZE] = {};
                int requestSize = recv(clients[i].data.fd, request, BUFFER_SIZE, 0);
                if (requestSize == -1)
                {
                    std::cout << "Error occurred while receiving a message\n";
                    if (epoll_ctl(epoll, EPOLL_CTL_DEL, clients[i].data.fd, nullptr) == -1)
                    {
                        std::cout << "Unable to delete from epoll\n";
                    }
                    if (close(clients[i].data.fd) == -1)
                    {
                        std::cout << "Error occurred on socket closing\n";
                    }
                    break;
                } else if (requestSize == 0) {
                    break;
                }
                int responseSize = 0, tries = 5;
                while (responseSize < requestSize)
                {
                    int sended = send(clients[i].data.fd, request + responseSize, requestSize - responseSize, 0);
                    if (sended == -1)
                    {
                        std::cout << "Error occurred on sending the message\n";
                        --tries;
                    }
                    responseSize += sended;
                    if (tries == 0)
                    {
                        std::cout << "Unable to send the message\n";
                        if (epoll_ctl(epoll, EPOLL_CTL_DEL, clients[i].data.fd, nullptr) == -1)
                        {
                            std::cout << "Unable to delete from epoll\n";
                        }
                        if (close(clients[i].data.fd) == -1)
                        {
                            std::cout << "Error occurred on socket closing\n";
                        }
                        break;
                    }
                }
            }
        }
    }
    closeAll(epoll, curSocket);
}
