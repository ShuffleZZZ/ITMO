#include <iostream>
#include <cstring>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>

const unsigned int BUFFER_SIZE = 1024, DEFAULT_PORT = 8080;
const char* TERMINATION_STRING = "Good bye\n";

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
        std::cout << "Wrong input: \n";
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
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(curSocket, (sockaddr*) &address, sizeof(address)) == -1)
    {
        std::cout << "Unable to connect client socket\n";
        return -1;
    }
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        std::cout << "Unable to create a pipe\n";
        if (close(curSocket) == -1)
        {
            std::cout << "Error occurred while closing the socket\n";
            return -1;
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
            return -1;
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
    curClient.data.fd = pipefd[0];
    if (epoll_ctl(epoll, EPOLL_CTL_ADD, pipefd[0], &curClient) == -1)
    {
        std::cout << "Unable to add current client to epoll\n";
        closeAll(epoll, curSocket);
        return -1;
    }
    char response[BUFFER_SIZE] = {};
    ssize_t code = recv(curSocket, response, BUFFER_SIZE, 0);
    if (code == -1)
    {
        std::cout << "Error occurred while receiving initial message\n";
        closeAll(epoll, curSocket);
        return -1;
    } else if (!code) {
        std::cout << "Unable to connect to server\n";
        closeAll(epoll, curSocket);
        return 0;
    } else {
        std::cout << response << '\n';
    }
    int pid = fork();
    if (pid == -1)
    {
        std::cout << "Error occured on forking\n";
        closeAll(epoll, curSocket);
        return -1;
    } else if (!pid) {
        if (close(pipefd[0]) == -1)
        {
            std::cout << "Error occured on closing of pipe\n";
            closeAll(epoll, curSocket);
            return -1;
        }
        std::cout << "Enter your requests below\n";
        while (true)
        {
            std::string message;
            std::cin >> message;
            if (write(pipefd[1], message.data(), message.size()) == -1)
            {
                std::cout << "Unable to send a message\n";
            }
        }
    } else {
        if (close(pipefd[1]) == -1)
        {
            std::cout << "Error occured on closing of pipe\n";
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
                char response[BUFFER_SIZE] = {};
                if (clients[i].data.fd == curSocket)
                {
                    ssize_t code = recv(curSocket, response, BUFFER_SIZE, 0);
                    if (code == -1)
                    {
                        std::cout << "Error occurred while receiving a message\n";
                        continue;
                    } else if (!code) {
                        std::cout << "Server isn't responding. " << TERMINATION_STRING;
                        std::cout << " _____ \n/ O O \\ \n|     | \n\\ \\_/ / \n ----- \n";
                        for (unsigned int j = 0; j <= i; ++j)
                        {
                            if (close(clients[j].data.fd) == -1)
                            {
                                std::cout << "Error occurred while closing the client socket\n";
                            }
                        }
                        if (close(epoll) == -1)
                        {
                            std::cout << "Error occurred while closing the epoll\n";
                            return -1;
                        }
                        return 0;
                    }
                    std::cout << "Response is: " << response;
                    if (strncmp(response, TERMINATION_STRING, strlen(TERMINATION_STRING)) == 0)
                    {
                        std::cout << " _____ \n/ O O \\ \n|     | \n\\ \\_/ / \n ----- \n";
                        closeAll(epoll, curSocket);
                        return -1;
                    } else {
                        std::cout << '\n';
                    }
                } else {
                    ssize_t code = read(clients[i].data.fd, response, BUFFER_SIZE);
                    if (code == -1)
                    {
                        std::cout << "Failed to read\n";
                        closeAll(epoll, curSocket);
                        return -1;
                    } else {
                        if (send(curSocket, response, code, 0) == -1)
                        {
                            std::cout << "Error occurred on sending the message\n";
                            closeAll(epoll, curSocket);
                            return -1;
                        }
                    }
                }
            }
        }
    }
    if (pid)
    {
        if (close(pipefd[0]) == -1)
        {
            std::cout << "Error occured on closing of pipe\n";
            return -1;
        }
    } else {
        if (close(pipefd[1]) == -1)
        {
            std::cout << "Error occured on closing of pipe\n";
            return -1;
        }
    }
    closeAll(epoll, curSocket);
    return 0;
}
